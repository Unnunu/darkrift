#!/usr/bin/env python3
"""
Obfuscate all non-SDK identifiers in the Dark Rift codebase.

Replaces all custom identifiers (functions, globals, structs, fields, enums, macros)
with deterministic SHA256-based names. Excludes C keywords, N64 SDK identifiers,
single-char names, and string literal contents.

Usage: python3 tools/obfuscate.py
"""

import hashlib
import json
import os
import re
import sys

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

C_SOURCE_DIRS = ["src", "include"]
C_EXTENSIONS = {".c", ".h"}
ASM_DIR = "asm"
ASM_EXTENSIONS = {".s", ".inc"}
CONFIG_FILES = [
    "symbol_addrs.txt",
    "undefined_syms_auto.txt",
    "undefined_syms.txt",
    "undefined_funcs_auto.txt",
]

EXCLUDE_PREFIXES = [
    os.path.join(PROJECT_ROOT, d)
    for d in ["ultralib", "expected", "build", "game_assets", "assets", "tools", ".git", "__pycache__"]
]
EXCLUDE_FILES = {
    "splat.yaml", "README.md", "configure.py", "diff_settings.py", "diff.py",
    ".gitignore", "checksum.sha1", "make_expected.sh", "permuter_settings.toml",
    "build.ninja", ".clang-format", ".ninja_log",
}

C_KEYWORDS = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "inline", "int", "long", "register", "restrict", "return", "short",
    "signed", "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while", "_Bool", "_Complex", "_Imaginary",
    "_Alignas", "_Alignof", "_Atomic", "_Static_assert", "_Noreturn", "_Thread_local",
    "__attribute__", "__attribute", "__packed__", "__inline__", "__extension__",
    "__builtin_va_list", "__builtin_va_start", "__builtin_va_end",
    "__typeof__", "__typeof", "__asm__", "__volatile__", "__const__", "__restrict__",
    "__FILE__", "__LINE__", "__func__", "__DATE__", "__TIME__", "__STDC__",
    "__STDC_VERSION__", "__cplusplus", "__ASSEMBLER__",
    "__section__", "__aligned__", "__unused__", "__used__",
    "define", "undef", "include", "ifdef", "ifndef", "elif",
    "error", "warning", "pragma", "line", "file", "defined",
}

N64_TYPES = {
    "u8", "s8", "u16", "s16", "u32", "s32", "u64", "s64", "f32", "f64",
    "size_t", "intptr_t", "uintptr_t", "wchar_t",
}

MIPS_REGS = {
    "zero", "at", "v0", "v1", "a0", "a1", "a2", "a3",
    "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "t8", "t9",
    "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
    "k0", "k1", "gp", "sp", "fp", "s8", "ra",
}

MIPS_INSNS = {
    "abs", "add", "addi", "addiu", "addu", "and", "andi",
    "b", "bal", "beq", "beql", "beqz", "bgez", "bgezl", "bgezal", "bgezall",
    "bgtz", "bgtzl", "bgt", "blez", "blezl", "ble", "bltz", "bltzl",
    "bc1f", "bc1fl", "bc1t", "bc1tl", "bltzal", "bltzall", "bne", "bnel", "bnez", "break",
    "cache", "ceil", "cfc1", "ctc1", "cvt",
    "dadd", "daddi", "daddiu", "daddu", "dbreak",
    "ddiv", "ddivu", "div", "divu", "dmult", "dmultu",
    "dneg", "dnegu", "dsll", "dsllv", "dsra", "dsrav", "dsrl", "dsrlv",
    "dsub", "dsubu",
    "eret",
    "floor", "float",
    "j", "jal", "jalr", "jr",
    "lb", "lbu", "ld", "ldc1", "ldl", "ldr", "lh", "lhu", "ll", "lui",
    "lt", "lw", "lwc1", "lwl", "lwr", "lwu",
    "madd", "maddu", "mfc1", "mfhi", "mflo", "mov", "move", "movn", "movz",
    "mtc1",
    "msub", "msubu", "mthi", "mtlo", "mul", "mult", "multu",
    "neg", "negu", "nop", "nor", "not",
    "or", "ori",
    "pref",
    "rnd", "round",
    "sb", "sc", "sd", "sdc1", "sdl", "sdr", "sh", "sll", "sllv",
    "slt", "slti", "sltiu", "sltu", "sqrt", "sra", "srav", "srl", "srlv",
    "sub", "subu", "sw", "swc1", "swl", "swr", "sync", "syscall",
    "teq", "tge", "tgeu", "tlt", "tltu", "tne", "trunc",
    "xor", "xori",
}

ASM_DIRECTIVES = {
    "glabel", "dlabel", "endlabel", "word", "half", "byte", "dword", "ascii", "asciz",
    "space", "align", "balign", "p2align", "global", "local", "set",
    "macro", "endm", "endmac", "rdata", "sdata", "text", "data", "bss",
    "section", "type", "size", "ent", "end", "frame", "mask", "fmask",
    "file", "abicalls", "cpload", "cprestore", "gpword", "gpdword",
    "module", "option", "struct", "endstruct", "export", "import",
    "nonmatching", "matching",
    "repeat", "endr", "irp", "irpc", "exitm", "eqv", "equiv",
    "def", "endef", "val", "scl", "tag", "ln",
    "r", "begin", "endproc",
    "include", "define", "undef", "pragma",
    "incbin", "noat",
    "hi", "lo", "gp_rel", "got", "got_disp", "got_page", "got_ofst",
    "dtag", "tag", "tls", "tprel", "tlsgd", "tlsldm", "gottprel",
}

MIPS_KEYWORDS = MIPS_REGS | MIPS_INSNS | ASM_DIRECTIVES


def collect_identifiers(text):
    return set(re.findall(r'\b([a-zA-Z_][a-zA-Z0-9_]+)\b', text))


def collect_identifiers_from_file(filepath):
    try:
        with open(filepath, "r") as f:
            return collect_identifiers(f.read())
    except (UnicodeDecodeError, OSError):
        return set()


def should_exclude_path(path):
    abs_path = os.path.abspath(path)
    for prefix in EXCLUDE_PREFIXES:
        if abs_path.startswith(prefix):
            return True
    return os.path.basename(path) in EXCLUDE_FILES


def get_files_to_process():
    files = []

    for src_dir in C_SOURCE_DIRS:
        dirpath = os.path.join(PROJECT_ROOT, src_dir)
        if not os.path.isdir(dirpath):
            continue
        for root, _, filenames in os.walk(dirpath):
            for f in filenames:
                ext = os.path.splitext(f)[1]
                if ext in C_EXTENSIONS:
                    filepath = os.path.join(root, f)
                    if not should_exclude_path(filepath):
                        files.append(filepath)

    asm_dir = os.path.join(PROJECT_ROOT, ASM_DIR)
    if os.path.isdir(asm_dir):
        for root, _, filenames in os.walk(asm_dir):
            for f in filenames:
                ext = os.path.splitext(f)[1]
                if ext in ASM_EXTENSIONS:
                    filepath = os.path.join(root, f)
                    if not should_exclude_path(filepath):
                        files.append(filepath)

    for cfg in CONFIG_FILES:
        filepath = os.path.join(PROJECT_ROOT, cfg)
        if os.path.isfile(filepath) and not should_exclude_path(filepath):
            files.append(filepath)

    return files


def build_n64_identifier_set():
    n64_ids = set(N64_TYPES)
    ultralib_dir = os.path.join(PROJECT_ROOT, "ultralib")
    if not os.path.isdir(ultralib_dir):
        return n64_ids

    for root, _, filenames in os.walk(ultralib_dir):
        for f in filenames:
            if f.endswith((".h", ".inc")):
                filepath = os.path.join(root, f)
                n64_ids.update(collect_identifiers_from_file(filepath))

    return n64_ids


def generate_mapping(identifiers, protected):
    protected_lower = {s.lower() for s in protected}
    mapping = {}
    used_names = set()

    for name in sorted(identifiers):
        if len(name) < 2:
            continue
        if name.lower() in protected_lower:
            continue
        if name in mapping:
            continue
        if name.startswith("D_") and len(name) > 2 and all(c in "0123456789ABCDEFabcdef" for c in name[2:]):
            continue
        if name.startswith("L") and len(name) > 1 and all(c in "0123456789ABCDEFabcdef" for c in name[1:]):
            continue
        if all(c in "0123456789ABCDEFabcdef" for c in name):
            continue

        h = hashlib.sha256(name.encode()).hexdigest()[:8]
        obf_name = f"x_{h}"
        while obf_name in used_names:
            h2 = hashlib.sha256((name + obf_name).encode()).hexdigest()[:8]
            obf_name = f"x_{h2}"
        mapping[name] = obf_name
        used_names.add(obf_name)

    return mapping


def replace_in_c(text, mapping):
    pattern = re.compile(
        r'("[^"\\]*(?:\\.[^"\\]*)*"'
        r"|\'[^\'\\]*(?:\\.[^\'\\]*)*\'"
        r"|//[^\n]*"
        r"|/\*[\s\S]*?\*/"
        r"|#[ \t]*include[ \t]*<[^>]*>"
        r"|\b([a-zA-Z_][a-zA-Z0-9_]{1,})\b"
        r")"
    )

    def replacer(m):
        if m.group(2):
            ident = m.group(2)
            return mapping.get(ident, ident)
        return m.group(0)

    return pattern.sub(replacer, text)


def replace_in_asm(text, mapping):
    pattern = re.compile(
        r'("[^"\\]*(?:\\.[^"\\]*)*"'
        r"|\'[^\'\\]*(?:\\.[^\'\\]*)*\'"
        r"|//[^\n]*"
        r"|/\*[\s\S]*?\*/"
        r"|;[^\n]*"
        r"|#[ \t]*include[ \t]*<[^>]*>"
        r"|#[^\n]*"
        r"|\b([a-zA-Z_][a-zA-Z0-9_]{1,})\b"
        r")"
    )

    def replacer(m):
        if m.group(2):
            ident = m.group(2)
            if ident.lower() in MIPS_KEYWORDS:
                return ident
            return mapping.get(ident, ident)
        return m.group(0)

    return pattern.sub(replacer, text)


def replace_in_config(text, mapping):
    pattern = re.compile(r'\b([a-zA-Z_][a-zA-Z0-9_]+)\b')
    return pattern.sub(lambda m: mapping.get(m.group(1), m.group(1)), text)


def process_file(filepath, mapping, file_type):
    with open(filepath, "r") as f:
        text = f.read()

    if file_type == "c":
        new_text = replace_in_c(text, mapping)
    elif file_type == "asm":
        new_text = replace_in_asm(text, mapping)
    else:
        new_text = replace_in_config(text, mapping)

    if new_text != text:
        with open(filepath, "w") as f:
            f.write(new_text)
        return True
    return False


def main():
    map_path = os.path.join(PROJECT_ROOT, "obfuscation_map.json")
    if os.path.exists(map_path):
        print("WARNING: obfuscation_map.json already exists. The code may already be obfuscated.")
        print("Run 'git checkout .' to restore original files, then re-run.")
        sys.exit(1)

    protected = set(C_KEYWORDS)

    print("Scanning N64 SDK for protected identifiers...")
    n64_ids = build_n64_identifier_set()
    protected.update(n64_ids)
    print(f"  N64 SDK identifiers: {len(n64_ids)}")

    print("Collecting project identifiers...")
    all_ids = set()
    files = get_files_to_process()
    if not files:
        print("ERROR: no files found to process!")
        sys.exit(1)

    for filepath in files:
        ids = collect_identifiers_from_file(filepath)
        all_ids.update(ids)

    print(f"  Total unique identifiers: {len(all_ids)}")
    print(f"  Files to process: {len(files)}")

    print("Generating obfuscation mapping...")
    mapping = generate_mapping(all_ids, protected)
    print(f"  Identifiers to rename: {len(mapping)}")

    print("Applying replacements...")
    modified_count = 0
    for filepath in files:
        ext = os.path.splitext(filepath)[1].lower()
        base = os.path.basename(filepath)
        if ext in C_EXTENSIONS:
            file_type = "c"
        elif ext in ASM_EXTENSIONS or base.endswith(".inc"):
            file_type = "asm"
        else:
            file_type = "config"

        if process_file(filepath, mapping, file_type):
            rel = os.path.relpath(filepath, PROJECT_ROOT)
            print(f"  Modified: {rel}")
            modified_count += 1

    with open(map_path, "w") as f:
        json.dump(mapping, f, indent=2, sort_keys=True)

    print(f"\nDone! Modified {modified_count}/{len(files)} files.")
    print(f"Mapping saved to obfuscation_map.json ({len(mapping)} entries)")


if __name__ == "__main__":
    main()
