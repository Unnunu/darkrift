# Dark Rift N64 Decompilation — Agent Documentation

## Project Overview
Matching decompilation of **Dark Rift** (1997), N64 3D fighting game by Kronos Digital Entertainment. Uses libultra SDK, IDO 5.3 compiler.

## Primary Goal: Complete Documentation
The end goal is to **fully document every identifier** in the codebase so a reader can understand the code as easily as possible:

1. **Source files** — rename all 49 `src/*.c` from hash names to meaningful names
2. **Functions** — add a comment above every function: what it does and how
3. **Inline comments** — insert brief comments every few lines within functions longer than ~5 lines
4. **Structs + fields** — name every struct, field, flag constant, and enum meaningfully
5. **Global variables** — name and document every global
6. **Subsystem docs** — create descriptions of how major subsystems work (AI, rendering, player state machine, audio, etc.)
7. **No logic changes** — matching decompilation constraint (only renames + comments)

> **All names are tentative.** Files, functions, structs, fields, and flags can be renamed again if a better name emerges from later analysis. Don't agonize — make a good-faith call and move on.

## Build System
- **Build command**: `ninja` (from root directory)
- **Regen after splat.yaml changes**: `./configure.py -c && ninja`
- **Output**: `darkrift.z64` (matching ROM)
- **Toolchain**: IDO 5.3 / GCC cross-compiler for MIPS

## Folder Structure
```
darkrift/
├── src/                    # 49 .c files (49 renamed, 0 hash-named)
├── include/
│   ├── common.h           # Main include
│   ├── common_structs.h   # All struct definitions (obfuscated names)
│   ├── enums.h            # All enum definitions (obfuscated)
│   ├── functions.h        # Function declarations
│   ├── variables.h        # Global variable declarations
│   └── macros.h           # Macros
├── ultralib/              # libultra SDK
├── asm/
│   └── nonmatchings/      # .s files for non-matched functions (per source hash)
├── tools/                 # splat_ext, extract_assets.py, obfuscation
├── game_assets/extracted/ # ROM asset dumps (SYM.txt, DB.txt — readable names)
└── ai/
    ├── AGENTS.md
    └── source_files/      # Per-file documentation JSON
```

## Asset Formats
- **WAD** — Archive container (folders + files)
- **TMD/KMD** — Model formats (hierarchy, textures, batches)
- **TEX** — CI4/CI8 textures with palettes
- **SP2/SP3** — Sprite sheets
- **DB** — Combat data (move tables, AI, hitboxes)
- **SYM** — Symbol tables for DB cross-referencing
- **ANM** — Animation data
- **K2/K3/K4/K5** — Model variants
- **SFB/SFX** — Audio (bank, sequence)
- **MOV** — Movie/intro data

## Core Data Structures (include/common_structs.h)
| Struct | Size | Description |
|--------|------|-------------|
| `Object` | 0x218 | Core game entity — position, velocity, transform, light, FSM context |
| `Player` | 0x5F50 | Full player state — Object ptr, move tables, AI state, 4x physics, models |
| `Transform` | 0x118 | Render transform — 2 Mtx + hierarchy links + quaternions |
| `Model` | 0x3D0 | 3D model — KMD data, batch transforms, per-part render info |
| `TaskNode` | 0xA0 | FSM controller — flags, callback stack (8 deep), params, next link |
| `FsmState` | 0x0C | FSM state — flags, callback, duration counter |
| `x_6fcfcf46` | 0x1F90 | Physics/collision state — velocity, transforms, batch info |
| `x_056d4f07` | 0x1458 | Shadow/effect renderer — projections, mesh data, 16 shadow instances |
| `x_ee01e8c6` | 0x12088 | Global GFX context — projection matrix, display list buffers, batch arrays |
| `x_80d298c9` | 0x38 | Resource load context — data ptr, name, size, type, ROM addr |

## Critical Rule: No Assumptions
**NEVER make assumptions or guesses.** Every conclusion must be based on:
- Source code evidence (string literals, unique API calls, data structure usage)
- Extracted game assets (`SYM.txt`, `DB.txt` — contain real symbol names)
- User's explicit answers
- Build verification (`ninja` / `./configure.py -c && ninja`)

If unsure, **ask the user**.

## Workflow Rules
1. **Only rename when 100% confident** — verify with build
2. **One file at a time** — rename → `./configure.py -c && ninja` → next
3. **No logic changes** — matching decompilation constraint
4. **Document "required to match" quirks** — compiler artifacts, not bugs
5. **Use extracted assets** as ground truth for naming
6. **Preserve @fake / @bug comments**

## Wave Methodology (Iterative Loose Deepening)

We use a **multi-wave approach** without rigid ordering, because understanding any one artifact (file, function, struct, field, flag) may depend on any other.

### Wave 0 — File renaming (scaffolding)
Rename all 49 source files from hash → meaningful name, one at a time, with build verification. Minimal documentation per file (2-3 sentence summary in `ai/source_files/<name>.json`). Purpose: build a navigation map.

### Wave 1 — Key functions
In named files, start documenting functions: what each does and how. If a flag/field/struct is unclear → skip it, log the question in the file's JSON (`open_questions`), move on.

### Wave 2 — Structs + fields
As function documentation clarifies struct field purposes, rename them. When a struct field is still opaque → skip, log question, move on.

### Wave 3 — Returns to open questions
Cyclically revisit `open_questions` in each file's JSON as new context accumulates from other files. Newly understood items may unlock previously skipped functions/structs.

### Core principles
- **No getting stuck**: if something is unclear after ~10–15 min of analysis → log the question, move on
- **Cross-pollination**: a function in file A may clarify a field in file B; a field in file C may clarify a function in file A
- **Open questions list**: each file JSON has an `open_questions` array updated as analysis progresses
- **Commit when asked only** — never commit without user request

## Renaming Policy (Wave 1+)

When a function/struct/field/enum/global is **understood with confidence**:

### Safe for global search/replace (bash/sed):
1. **Functions** — unique names, rename across .c, .h, functions.h, variables.h, JSON docs
2. **Struct/Type names** — unique, rename in common_structs.h, functions.h, variables.h, all .c files, JSON docs
3. **Enums** — unique names, rename in enums.h, all .c files, JSON docs
4. **Global variables** — unique names, rename in variables.h, all .c files, JSON docs
5. **Static variables** — unique names, rename in their .c file only
6. **Macros** — unique names, rename globally

### DO NOT bulk replace (user renames in VS Code via F2):
- **Struct fields** — same field name may exist in multiple structs (e.g., `flags`, `callback`, `next`). User must use go-to-definition (F2) to rename only the intended struct's field.

### In-place within function body:
- **Function parameters & local variables** — rename directly in the function where used.

### Process:
1. Agent proposes renames for safe identifiers → user approves
2. Agent runs bash/sed to apply globally
3. Agent provides struct field rename list → user applies in VS Code
4. Build verify: `./configure.py -c && ninja`
5. Update JSON docs

All names tentative — can be renamed again if better understanding emerges.

## Documentation Sync

After documenting/renaming in a file:
- Update `ai/source_files/<name>.json` with function summaries, renamed identifiers, and open questions.
- Keep JSON in sync with source code.

## Naming Conventions (Casing)

| Category | Convention | Example |
|----------|------------|---------|
| Struct/Type names | PascalCase | `TaskNode`, `FsmState`, `TaskPool` |
| Function names | snake_case | `task_execute`, `task_append` |
| Global variables | camelCase with `g` prefix | `gTaskPool`, `gTaskLock` |
| Static variables | camelCase with `s` prefix | `sFrameCounter`, `sDebugMode` |
| Struct fields | snake_case | `flags`, `callback`, `delay`, `stack_ptr` |
| Local variables | snake_case | `task`, `prev`, `flags` |
| Macro names | UPPER_SNAKE_CASE | `TASK_POP(task)` |
| Enum type names | PascalCase | `TaskFlag`, `PushCondition` |
| Enum entries | UPPER_SNAKE_CASE | `TASK_RUNNABLE`, `TASK_TIME_BASED` |

Rationale: Matches existing named code in project (e.g., `Object`, `Player`, `Transform` are PascalCase; `player_replay_record` is snake_case).

## File Rename Progress

### How files are identified
- **Gold standard**: self-identifying `"name.c"` string literal in `x_56c3086a(..., "name.c", line)` assert/error calls
- **Strong evidence**: unique libultra API usage (osCont*, guPerspective, alSeqp*, etc.), unique patterns (static Gfx D lists), cross-references
- **Always verified**: rename file + update splat.yaml → `./configure.py -c && ninja`

### Renamed (49/49)
| Hash | Name | Evidence |
|------|------|----------|
| `cac92df6` | `audio` | String `"audio.c"`, alSeqp*/alSndp*/alSyn* API |
| `d6c43c79` | `boot` | osInitialize, VI/PI mgr, thread create |
| `13e5c685` | `controller` | osContInit/ReadData/GetReadData |
| `e464307e` | `rsp` | osSpTaskStart, Thread 4 scheduler |
| `a8ef58b5` | `memory` | Heap allocator (best-fit) + DMA |
| `cbf2ec05` | `main` | x_14ae77a0 game loop, segment renamed `main` |
| `1f557ef1` | `gfx_data` | Static DLs, OSTask M_GFXTASK, DR ucode |
| `38d952c0` | `wad` | String `"wad.c"`, WAD loader |
| `d53dbdfd` | `kmd` | String `"kmd.c"`, KMD/TMD parser |
| `4a248257` | `scroll` | String `"scroll.c"`, scroll/background |
| `7c0f8cf9` | `model` | String `"model.c"`, 3D model hierarchy |
| `346e1e19` | `item` | String `"item.c"`, Object pool |
| `a46ab948` | `camera` | String `"camera.c"`, camera math |
| `02989789` | `player` | Player FSM, char init (.tmd/.k3/.MOV/.db), move selection, replay |
| `39e934c2` | `menu` | Screen/menu flow: logos → title → char select → options → endings |
| `5c37bf8b` | `combat` | Hit detection, damage resolution, collision volumes, hit effects |
| `716adc37` | `trail` | Weapon trail afterimage (Catmull-Rom spline, triangle-strip ribbon) |
| `3b281efc` | `transform` | Matrix math, Transform hierarchy, trig tables, RSP prep |
| `04859e8a` | `match` | Match flow: char select → round mgmt → HUD → post-battle |
| `108260c9` | `select` | Selection UI: options, char select grid, stage select, digit render |
| `2435583e` | `present` | Presentation screens: title, Kronos, attract, win results, The End |
| `3f72e5c8` | `background` | Tiled scrolling background (.pcl + .GMD, frustum cull) |
| `d5fd353d` | `aibrain` | AI opponent behavior (reaction tables, difficulty, distance) |
| `a7cab0a2` | `pregame` | Pre-match setup: char select screen, handicap, cheats, practice |
| `49be7a13` | `projectile` | Projectile/effect system (ring, homing, held, guard prediction) |
| `698a4622` | `sparks` | Spark/debris particles (GT ucode, gravity, bounce, white→blue fade) |
| `8b713856` | `move` | Move/attack state machine (animation scheduler, combo chains, sound triggers) |
| `40f8a510` | `buttons` | Controller input processing (remap, analog→d-pad, lock/filter) |
| `134911bd` | `fighters` | Character data tables (names, moves, hitboxes, state machine, palettes) |
| `573e99f1` | `huffman` | Adaptive Huffman tree decoder + bit I/O for LZSS |
| `274fc753` | `lzss` | LZSS decompression (sliding window 4096, DMA streaming) |
| `992e0686` | `hud` | HUD: health bars, score digits, portraits, timer, results |
| `f5b5f599` | `fighter` | Per-fighter config data (collision volumes, groups) |
| `4e62f251` | `eff_fire` | Fire attack VFX (3-stage shockwave rings, fire particle) |
| `78a17f74` | `ply_init` | Player model/render state init wrapper |
| `b1eb6a03` | `char_cfg` | Per-fighter config (health, damage, spawn, hitboxes) |
| `a8c9742a` | `char_moves` | Per-fighter moveset (animation sequences, frame events) |
| `bd5da974` | `char_gore` | Per-fighter data (frame timings, combo chains, hitbox frame triggers) |
| `cc5f71fc` | `char_eve` | Per-fighter data (collision volume, bone links, sphere attach) |
| `6a1b262c` | `char_morp` | Per-fighter data (stats, shop entries, ID lists) |
| `656c3c84` | `char_niik` | Per-fighter data (bone mapping, combo chains, attack IDs) |
| `04ed7558` | `char_scar` | Per-fighter data (bone mapping, hitbox offsets, anim tables) |
| `31382929` | `char_sono` | Per-fighter data (bone mapping, hitbox offsets, anim tables) |
| `94a3c513` | `char_zenmuron` | Per-fighter data (bone mapping, hitbox offsets, anim tables) |
| `01c1f892` | `cam_follow` | Battle camera: 2-player orbital follow, split-screen, auto-face, boundary wrap |
| `ac8d9591` | `eff_hit` | Hit impact VFX: dust, camera shake, combo routing, knockdown |
| `1b3b963c` | `practice` | Training mode: config UI, combo playback, input display, HUD |
| `df73244f` | `task` | Task scheduler/FSM (implements task.h) |

### Still hash-named (0)
All 49 source files renamed.

Also: `kdebugserver` (already correctly named).

## Wave 1 Progress

### Task Scheduler (task.c/h) — DONE
Functions renamed and documented: `task_execute`, `task_free_list`, `task_find_by_id`, `task_append`, `task_remove_current`. Globals: `gTaskLock`, `gTaskPool`. Macros: `TASK_END`. Enum entries: `TASK_RUNNABLE`, `TASK_TIME_BASED`, `TASK_FRAME_BASED`, `TASK_PUSH`, `TASK_FORCE_PUSH`, `TASK_SAVE_STACK`, `TASK_POP`.

### Boot/Init (boot.c) — DONE
Functions: `boot_entry`, `idle_thread_func`, `main_thread_func`. All 22 globals renamed: threads (sIdleThread, sMainThread, sRspThread), stacks (sIdleStack, sMainStack, sRspStack), message queues (gPiMessageQueue, gRspMessageQueue, sPiMgrMesgQueue, sViEventQueue, sSpEventQueue, sDpEventQueue, sContMesgQueue), messages arrays, padding. Macro `ARRAY_COUNT` renamed globally. Also renamed: `controller_init`, `main_game_loop`, `rsp_scheduler_thread`, `sBootFlags`. Updated symbol_addrs.txt, entry.s, functions.h, variables.h, macros.h, rsp.c, controller.c, main.c, audio.c, memory.c, huffman.c.

### Player (player.c) — DONE (Wave 1)
All 27 functions renamed and documented. 5 structs renamed (ReplayEntry, ReplayBuffer, DbFileHeader, AiTacticEntry, AiEntryHeader). Key renames: `player_init`, `player_reinit`, `player_ai_check`, `player_exec_state`, `player_exec_move_ai`, `player_select_move`, `replay_record`, `replay_playback`. Updated nonmatching .s files, symbol_addrs.txt, functions.h, and 6 caller files (menu.c, match.c, move.c, hud.c, aibrain.c, eff_hit.c, combat.c). Also renamed `shadow_init` in trail.c.

### Combat (combat.c) — DONE (Wave 1)
All 12 functions renamed and documented. 7 globals renamed. Key renames: `hit_effect_fade_slow`, `hit_effect_fade_fast`, `spawn_hit_effect`, `point_in_hit_range`, `find_collision_point`, `hit_outcome`, `apply_hit`, `hit_detect_lower/upper/grounded_a/grounded_b`, `coll_volume_setup`. Globals: `sColorRed`, `sColorBlue`, `sHitModelRegular`, `sHitModelGrab`, `sScratchPos`, `sCombatPad`, `sCombatScratch`. Updated callers in eff_hit.c, projectile.c, player.c, menu.c. Updated functions.h, variables.h, nonmatching .s. Build verified.

Next in queue: cam_follow.c, transform.c, model.c, memory.c

## Thread Model
| Pri | Thread | Entry | Description |
|-----|--------|-------|-------------|
| 1 | IDLE | boot_entry → idle_thread_func | osInitialize, VI/PI mgr, creates Thread 3+4 |
| 3 | MAIN | main_thread_func → main_game_loop | Game init, scheduler queues, game loop |
| 4 | RSP | rsp_scheduler_thread in `rsp.c` | RSP task dispatch, audio/SI/SP/DP/VI event handling |

## Useful Commands
```bash
# Regen build system + build (after splat.yaml rename)
./configure.py -c && ninja

# Build only (no splat regen)
ninja

# Extract assets
python3 tools/extract_assets.py

# Search identifiers
grep -r "x_XXXXXXXX" src/ include/
```
