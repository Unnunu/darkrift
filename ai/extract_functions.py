#!/usr/bin/env python3
"""Extract function signatures from a C file for documentation."""

import re
import sys
import json
from pathlib import Path

FUNC_RE = re.compile(
    r'^(?:static\s+)?(?:inline\s+)?'
    r'(?:void|u8|u16|u32|u64|s8|s16|s32|s64|f32|f64|char|int|'
    r'x_[a-f0-9]{8}|[A-Za-z_][A-Za-z0-9_]*)\s*'
    r'(\*?\s*)?'
    r'(x_[a-f0-9]{8}|[A-Za-z_][A-Za-z0-9_]*)\s*'
    r'\([^)]*\)\s*\{',
    re.MULTILINE
)

def extract_functions(filepath):
    """Extract function names and their line numbers from a C file."""
    with open(filepath, 'r') as f:
        content = f.read()

    functions = []
    for match in FUNC_RE.finditer(content):
        name = match.group(2)
        if name and not name.startswith('x_') or True:
            line_num = content[:match.start()].count('\n') + 1
            functions.append({"name": name, "line": line_num})
    return functions

def generate_doc_stub(func_name):
    """Generate a documentation stub for a function."""
    return f"/**\n * {func_name} - \n * \n * Returns: \n * Params: \n */"

def main():
    if len(sys.argv) < 2:
        print("Usage: extract_functions.py <c_file> [--json]")
        sys.exit(1)

    filepath = sys.argv[1]
    funcs = extract_functions(filepath)

    if "--json" in sys.argv:
        print(json.dumps(funcs, indent=2))
    else:
        for f in funcs:
            print(f"{f['line']:4d}: {f['name']}")

if __name__ == "__main__":
    main()