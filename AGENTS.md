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
├── ai/
│   └── source_files/      # Per-file documentation JSON
└── AGENTS.md              # This file (agent documentation)
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
| `TaskNode` | 0xA0 | Task controller — flags, callback, TaskFrame stack (8 deep), params, next link |
| `TaskFrame` | 0x0C | Task stack frame — flags, callback, duration counter. Renamed from `FsmState` (was a semantic mismatch — it's a stack frame, not an FSM state). |
| `ScreenProfile` | 0x20 | Screen/config profile — init func, clear/fog colors, fog distances, camera bounds, ambient color |
| `RenderCallback` | — | `s32 (*)(void *)` — render setup callback function pointer type |
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
2. **No logic changes** — matching decompilation constraint
3. **Document "required to match" quirks** — compiler artifacts, not bugs
4. **Use extracted assets** as ground truth for naming
5. **Preserve @fake / @bug comments**

## Collaboration Model (Wave 1+)

**Agent proposes rename mapping → User applies in source → Agent updates docs only.**

The agent **never writes code** during renaming — only updates `ai/source_files/*.json` documentation.

### Process:
1. Agent analyzes files and produces a complete rename mapping (old → new)
2. User applies all renames in VS Code / sed / manually
3. User runs `ninja` to verify the build
4. On success, Agent updates `ai/source_files/<name>.json` for affected files
5. Agent updates the Wave Progress section in AGENTS.md

### What Agent owns:
- `ai/source_files/*.json` — function summaries, renamed identifiers, open questions
- `AGENTS.md` — Wave Progress section

### What User owns:
- All code edits: `.c` files, `.h` files, `.s` files, `symbol_addrs.txt`, `splat.yaml`
- Build verification: `ninja`

### All names tentative
Can be renamed again if better understanding emerges.

## Documentation Review

Run on demand via command `Сделай проверку файла <name>` (or `Review file <name>`).

**Act as a human reading the code.** Review the named source file and identify:

1. **Unclear names** — functions, structs, fields, flags, globals that still have obfuscated hash names or **misleading names**. Also check **name consistency across related declarations** — does a message queue and its backing buffer share a coherent naming theme? Does a function's name match what it actually does at every call site? Watch for **semantic mismatches**: a name implying one pattern (FSM, singleton, manager, handler, state) when the code actually does something else (stack frame, utility, allocator, flag).
2. **Missing comments** — functions without `// what it does and how` header comments
3. **Opaque logic** — blocks of code where the intent isn't obvious from names alone
4. **Weird/buggy patterns** — `@bug` / `@fake` / `NON_EQUIVALENT` / dead code, compiler artifacts that need documenting
5. **Unclear cross-references** — calls to external functions whose purpose in this context isn't obvious
6. **Open questions** — anything you can't figure out within ~5 min of analysis

### Output format
For each issue found:
```
- `<file.c>:<line>` — <what's wrong> → <suggested fix / question>
```

### Caveats
- Matching decompilation constraint: **no logic changes**, only renames + comments
- If something is unclear after 5 min, flag it and move on
- If the file is clean (all names clear, well-commented, no opaque logic), say "Файл чист, нареканий нет"

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

## Naming Conventions (Casing)

| Category | Convention | Example |
|----------|------------|---------|
| Struct/Type names | PascalCase | `TaskNode`, `TaskFrame`, `TaskPool` |
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
Functions renamed and documented: `task_execute`, `task_free_list`, `task_find_by_id`, `task_append`, `task_remove_current`. Globals: `gTaskLock`, `gTaskPool`. Struct: `FsmState` → `TaskFrame` (semantic mismatch — it's a stack frame, not FSM state). Macros: `TASK_END`. Enum entries: `TASK_RUNNABLE`, `TASK_TIME_BASED`, `TASK_FRAME_BASED`, `TASK_FLAG_10`, `TASK_FLAG_20`, `TASK_SAVE_STACK`, `TASK_POP`.

### Boot/Init (boot.c) — DONE
Functions: `boot_entry`, `idle_thread_func`, `main_thread_func`. All 22 globals renamed: threads (sIdleThread, sMainThread, sRspThread), stacks (sIdleStack, sMainStack, sRspStack), message queues (gPiMessageQueue, gRspMessageQueue, sPiMgrMesgQueue, sViEventQueue, sSpEventQueue, sDpEventQueue, sContMesgQueue), messages arrays (sSchedMesgs → sPiMesgs), padding. Macro `ARRAY_COUNT` renamed globally. Also renamed: `controller_init`, `main_game_loop`, `rsp_scheduler_thread`, `sBootFlags`. Updated symbol_addrs.txt, entry.s, functions.h, variables.h, macros.h, rsp.c, controller.c, main.c, audio.c, memory.c, huffman.c.

### Player (player.c) — DONE (Wave 1)
All 27 functions renamed and documented. 5 structs renamed (ReplayEntry, ReplayBuffer, DbFileHeader, AiTacticEntry, AiEntryHeader). Key renames: `player_init`, `player_reinit`, `player_ai_check`, `player_exec_state`, `player_exec_move_ai`, `player_select_move`, `replay_record`, `replay_playback`. Updated nonmatching .s files, symbol_addrs.txt, functions.h, and 6 caller files (menu.c, match.c, move.c, hud.c, aibrain.c, eff_hit.c, combat.c). Also renamed `shadow_init` in trail.c.

### Combat (combat.c) — DONE (Wave 1)
All 12 functions renamed and documented. 7 globals renamed. Key renames: `hit_effect_fade_slow`, `hit_effect_fade_fast`, `spawn_hit_effect`, `point_in_hit_range`, `find_collision_point`, `hit_outcome`, `apply_hit`, `hit_detect_lower/upper/grounded_a/grounded_b`, `coll_volume_setup`. Globals: `sColorRed`, `sColorBlue`, `sHitModelRegular`, `sHitModelGrab`, `sScratchPos`, `sCombatPad`, `sCombatScratch`. Updated callers in eff_hit.c, projectile.c, player.c, menu.c. Updated functions.h, variables.h, nonmatching .s. Build verified.

### Battle Camera (cam_follow.c) — DONE (Wave 1)
All 25 functions renamed and documented. Key renames: `cam_battle_update`, `cam_update`, `cam_distance_update`, `cam_save_state`, `cam_save_state_alt`, `cam_cinematic_update`, `cam_intro_skip_check`, `cam_intro_wait_input`, `cam_intro_start(_inverse)`, `cam_battle_init`, `cam_ko_orbit/init`, `cam_debug_controls/scene_input/init`, `cam_face_players`, `cam_world_shift/wrap/wrap_reset`, `cam_boundary_check`, `cam_project_point`, `lerp_int`, `angle_diff`, `iabs`. Updated callers in player.c, move.c, eff_hit.c, menu.c, match.c, present.c. Updated functions.h, nonmatching .s (x_7cdfb63d.s, hit_effect_angle_anim.s). NON_EQUIVALENT asm functions noted. Build verified.

### Transform (transform.c) — DONE (Wave 1)
Functions renamed and documented: `mat4_ident`, `mat4_ident_partial`, `mat4_copy`, `mat4_mult`, `quat_from_axis`, `quat_from_euler`, `quat_to_matrix`, `transform_set_identity`, `transform_update_node`, `transform_update_model`, `anim_setup_bone_matrix`, `anim_bone_matrix_mul`. Globals: `sSinTable`, `sCosTable`, `gTrigTable`. Updated all callers across 7 files. Updated functions.h, variables.h, nonmatching .s (x_e36ec0fe.s). Build verified.

### Model (model.c) — DONE (Wave 1)
40 functions renamed: `model_texture_register`, `texture_shift_full/line`, `model_texture_reset`, `model_collect_textures`, `model_light_pool_init/attach/detach`, `model_render_mode_zbuf/standard/setup`, `model_parts_enable_all/disable_all`, `model_visibility_sync/set`, `model_prim_color_update/check`, `model_node_centroid(_direct)`, `model_anim_setup_transforms/sort/setup_dl`, `model_bone_setup`, `model_part_draw`, `model_shadow_render/spawn`, `model_traverse_transforms`, `model_transforms_update`, `model_anim_blend_weighted/absolute/additive`, `model_anim_tick/duration`, `model_bones_reset`, `model_anim_load`, `model_sort_entries`, `model_anim_render`, `model_frame_render`, `model_lighting_apply`, `model_render`. Globals: `sShadowDesc`, `sUnusedMatrix`, `sDisplayList`, `sSortListHead`, `sLightListHead`, `sLightFreeList`, `sFurTextures`, `sFurTextureCount`. Build verified.

### Memory (memory.c) — DONE (Wave 1)
19 functions renamed: `mem_delay`, `mem_pool_init`, `mem_defrag`, `mem_free_add`, `mem_validate`, `mem_free_space`, `mem_list_prepend/remove`, `mem_merge_free`, `mem_alloc/free`, `mem_set`, `mem_copy_overlap`, `mem_dma_alloc/free`, `dma_read_sync/async`, `mem_dma_set_callback`, `mem_alloc_debug`. 11 globals: `sMemFreeList`, `sMemUsedList`, `sDefragNeeded`, `sDmaMesg`, `sMemAllocated`, `sMemFreeBytes`, `sDmaSlots`, `sDmaSlotCount`, `sHeapBase`. Build verified.

### RSP (rsp.c) — DONE (Wave 1)
10 functions renamed: `rsp_clear_callbacks`, `rsp_register_callback`, `rsp_clear_screen`, `rsp_task_init`, `rsp_scheduler_thread`, `rsp_submit_gfx_tasks`, `rsp_wait_idle`, `rsp_vi_sync`, `rsp_game_init` (NON_EQUIVALENT), `rsp_game_reinit`. 24 globals renamed: static BSS (sClearColorR/G/B, sOverlayBrightness, sFadeThreshold, sGfxTaskCount, sFramebuffer, sZbuffer, sFbBusy, sClearZbuffer, gGfxFlags, sFogColorR/G/B, sFogMin, sFogMax, sRenderCallbacks[20], sRenderCallbackArgs[20], sZbufFillSkipped, sRspStatus, sRspSyncState, sCurrentTaskType), OSTasks (sGfxTaskF3D, sGfxTaskDR, sGfxTaskExtra), timing (gRspTimeTotal, gRdpTimeTotal), write pointers (gF3dDisplayListPtr, gF3dExtraListPtr, gDrBatchPtr). Types: `x_1c3c0f22` → `RenderCallback`, `x_cc16c016` → `UnkStruct10`. Enum `x_a58c44e6` → `GfxFlags` renamed (GFX_NONE, GFX_SKIP_SCENE, GFX_EXTRA_DL, GFX_FLAG_4, GFX_NO_ZCLEAR, GFX_SHADOW_MODE, GFX_MENU_OVERLAY, GFX_BORDER_AROUND). Updated 35 files across the codebase. Build verification pending user.

### ScreenProfile struct (common_structs.h) — Renamed
`x_d0fba50a` → `ScreenProfile`. Fields renamed: `x_b8173ab8` → `clearColorR`, `x_d863406f` → `clearColorG`, `x_f6c089c5` → `clearColorB`, `x_f74c4cfa` → `clearColorA`, `x_60c27ea9` → `fogColorR`, `x_ee25ce89` → `fogColorG`, `x_747e2503` → `fogColorB`, `x_876a16f1` → `fogColorA`, `x_d23de2ad` → `fogMin`, `x_55739355` → `fogMax`, `x_08b62e4f` → `cameraBounds`, `x_389f2997` → `ambientColor`. Array `x_4540c33c[]` → `gScreenProfiles[]`.

### Main (main.c) — DONE (Wave 1)
15 functions renamed: `main_game_loop`, `gfx_render_frame`, `gfx_init_frame`, `tr_obj_alloc`, `tr_player_load`, `tr_scene_loop`, `tr_quad_opaque` (NON_MATCHING), `tr_quad_xlu` (NON_MATCHING), `tr_fade_start`, `tr_fade_in_setup`, `tr_fade_in`, `tr_fade_hold`, `tr_scene_change`, `tr_fade_out_delay`, `tr_fade_out`, `func_80001C6C` (attract entry). 19 globals renamed: sQuadVtx, sQuadTri, sZeroVelocity, sZeroPosition, sDefaultLights, gCurrentScreenId, sPrevScreenId, sRenderTimeAccum, sFrameCounter, sFadeAlpha, sQuadBatch, sQuadDl, sScratchMtx, gFramebuffers, gOverlayDlPtr, gExtraBatchPtr, D_8005BFCE (fb index), x_e30d50d2 (state flags), x_e38a6e19 (screen ID). Macro g_PERSPNORM. Updated functions.h, variables.h. Build verification pending user.

### Buttons (buttons.c) — DONE (Wave 1)
5 functions renamed: `button_remap`, `button_remap_reset`, `button_process` (NON_MATCHING), `button_update_frame`, `button_state_reset`. 5 globals renamed: `sCButtonLut[16]`, `sTriggerLut[8]`, `sDPadLut[11]`, `sFaceLut[16]`, `gRemapTable[2][8]`. Pipeline: raw OSContPad.button → 4-nibble LUT → analog→d-pad (±40) → remap → mirror (swap L↔R) → lock/filter → final buttons. Updated rsp.c (2 call sites), main.c (1 call site), select.c, menu.c. `button_update_frame` called from `gfx_render_frame`. Build verification pending user.

### Controller (controller.c) — DONE (Wave 1)
2 functions: `controller_init` (already named), `controller_read_frame` (was `x_bb61051c`). 7 globals renamed: `sNullPad`, `sControllerCount`, `sSiMessageQueue`, `sSiMesg[1]`, `sContStatus[4]`, `sContPad[4]`, `gContPadPtrs[4]`. SI event queue + osContInit/ReadData. Updated rsp.c, controller.c, buttons.c, main.c. Build verification pending user.

### Huffman (huffman.c) — DONE (Wave 1)
8 functions renamed: `lzhuf_dma_refill`, `lzhuf_read_byte`, `lzhuf_read_bit`, `lzhuf_read_byte_bits`, `lzhuf_read_bits`, `lzhuf_tree_init`, `lzhuf_tree_rebuild` (NON_EQUIVALENT), `lzhuf_tree_update`. 5 macros renamed: `THRESHOLD`, `NUM_SYMBOLS`, `TREE_SIZE` → kept as `T`, `TREE_ROOT` → kept as `R`, `MAX_FREQ`. 20 globals renamed: `sDistBase`, `sDistExtra`, `sBitBuf`, `sBitCount`, `sBitMask[17]` (@bug element 15), `sBitShift[16]`, `sHufPad[4]`, `sDecompBufs[2]`, `sDecompReadPtr`, `sDecompWritePtr`, `sDecompRemain`, `sDecompChunkIdx`, `sDecompBufIdx`, `sDecompBufPos`, `sDecompChunkSize`, `sDecompLastFlag`, `sDecompResCtx`, `sSlideWindow[4160]`, `sHufFreq[628]`, `sHufTree[944]`, `sHufMap[628]`. Updated lzss.c (all externs), wad.c (call site). Build verified.

### LZSS (lzss.c) — DONE (Wave 1)
4 functions renamed: `lzhuf_decode_symbol`, `lzhuf_decode_distance`, `lzhuf_decompress`, `lzhuf_start` (was `x_69c2895e`). All extern declarations updated to match huffman.c renames. Window N=4096, max match F=60, threshold=2, double-buffered DMA streaming. Entry called from wad.c. Build verified.

### Item/Object Pool (item.c) — DONE (Wave 1)
19 functions renamed: `pool_init`, `pool_expand`, `pool_expand_both`, `pool_init_core`, `obj_alloc`, `obj_free`, `obj_init` (NON_EQUIVALENT), `obj_setup_transforms`, `obj_create_anim`, `obj_create_task`, `obj_create_from_def`, `obj_create_with_model`, `obj_create_from_props`, `obj_create_with_model_ptr`, `obj_create_frame_render`, `obj_collide_all`, `obj_scene_update`, `batch_ident`, `batch_null_iter` (last 2 unused). 5 globals renamed: `gObjectList`, `sObjectCount`, `gObjectPool`, `gPhysicsPool`, `sItemUnused`. Updated main.c, match.c, cam_follow.c, practice.c, functions.h, variables.h. Build verified.

### WAD Archive (wad.c) — DONE (Wave 1)
Enum `WadFileType` (22 types mapped by extension: WAD_ANM, WAD_TEX, WAD_SP2, WAD_DB, WAD_PCL, WAD_GMD, WAD_TMD, WAD_SEQ, WAD_CTL, WAD_TBL, WAD_SP3, WAD_SFB, WAD_SFX, WAD_K2/K3/K4/K5, WAD_MOV, WAD_OC, WAD_SYM, WAD_VOX, WAD_NESTED). 4 structs: `WadFolder`, `WadFileEntry`, `WadHeader`, `WadAnmHeader`. 42 functions renamed: loaders per type (`wad_load_anm/tex/sp2/kmd_0/gmd/tmd/ctl/vox/sfb/sp3/oc/k2/k3/k4/k5/mov/sym`), resolvers (`wad_resolve_*`), management (`wad_open/open_path/load_path/unload_*`), entry mgmt (`wad_entry_*`), helpers (`wad_streq/strcat/strcpy/strupr`). 14 globals: `sWadEntries`, `sWadEntryCount`, `sWadHeader`, `sWadDataPtr`, `sWadFolder`, etc. Updated functions.h, variables.h, symbol_addrs.txt, 30+ caller files.

### Audio (audio.c) — DONE (Wave 1)
25 functions renamed: `audio_ostask_init`, `audio_state_reset`, `audio_init`, `audio_heap_alloc`, `audio_reinit`, `audio_synth_config`, `audio_frame_render`, `audio_dma_callback`, `audio_get_dma_proc`, `audio_dma_wait`, `audio_frame_update`, `audio_submit_task`, `audio_sfx_play`, `audio_sfx_stop`, `audio_sfx_stop_bank`, `audio_sfx_stop_all`, `audio_bgm_stop`, `audio_fade_complete`, `audio_fade_out_task`, `audio_fade_in_task`, `audio_sfx_set_pan`, `audio_sfx_set_vol`, `audio_bgm_set_vol`, `audio_unmute`, `wad_setup_sfx_bank`. 5 structs: `AudioConfig`, `AudioDmaBuf`, `AudioBufEntry`, `AudioBufPool`, `AudioFrameCtx`. ~50 globals: `sAudioConfig`, `sAlSeqPlayer`, `sAlSndPlayers`, `sAlHeap`, `sAudioHeapData`, `sAlBankFile`, `sMusicVolume`, `sSfxVolume`, `sBgmPlaying`, `sSfxPlaying`, `sAudioMuted`, `sSfxBankLoaded`, `sSfxSoundCount`, `sSfxVolumeSetting`, `sMusicVolumeSetting`, `sAudioTask`, etc. Updated functions.h, variables.h, symbol_addrs.txt, wad.c, present.c, match.c, move.c, hud.c. Build verified.

### Move/Attack (move.c) — DONE (Wave 1)
15 functions renamed: `move_exec_current`, `move_delay_cb`, `move_osc_up`, `move_osc_down`, `move_count_up`, `move_apply_vel`, `move_to_next`, `move_camera_trig`, `move_state_change`, `move_anim_change`, `move_exec_init`, `move_init_cb`, `move_retry_cb`, `move_sfx_trig`, `move_null_cb`. Used x_388306ba (attack entry) and x_c8184673 (SFX frame trigger) structs. Updated callers in player.c, eff_hit.c, fighters.c. Build verified.

### Projectile/Effects (projectile.c) — DONE (Wave 1)
16 functions renamed: `projectile_fade_cb`, `projectile_frame_update`, `projectile_init`, `projectile_null_cb`, `projectile_hit_dispatch`, `projectile_end`, `projectile_ring_update`, `projectile_homing_update`, `projectile_hit_spawn`, `projectile_guard_spawn`, `projectile_special_check`, `projectile_spawn`, `guard_prediction_check`, `projectile_homing_setup`, `projectile_guard_homing` (NON_EQUIVALENT), `projectile_impact_check`. 1 global: `sProjectileTypeTable` (unused). Updated callers in eff_hit.c, eff_fire.c, fighters.c, present.c. Build verified.

### Hit Effects (eff_hit.c) — DONE (Wave 1)
All 62 functions renamed and documented. 11 globals renamed: `sHitDustSpriteDef`, `sHitDustFrameTable`, `sHitEffectObj`, `sHitAngleA/B/Target/Vel/Accel/Step[2]`, `sHitDustLastPos[2]`, `sHitAngleSum[2]`, `sHitPushbackDist[2]`. Key renames: `hit_task_override`, `hit_clear_attacked_flag`, `hit_combo_routing`, `hit_dust_trail`, `hit_cam_rotate_to_opponent`, `hit_effect_angle_anim` (NON_EQUIVALENT), `hit_check_facing_away`, `hit_knockback_gravity`, `hit_combo_counter_attack`. Updated fighters.c (30 decls + 50 call sites), functions.h (3 decls), variables.h (6 decls), player.c (6 + 4), aibrain.c (1), combat.c (1), eff_fire.c (1), projectile.c (1), match.c (3). Build verification pending.

### Fire Effects (eff_fire.c) — DONE (Wave 1)
4 functions renamed: `fire_null_cb`, `fire_ring_update_cb`, `fire_wave_spawn_cb`, `fire_wave_init_cb`. 2 globals: `sFireFlag`, `sFireCounter`. Updated projectile.c (1 call site), functions.h (1 decl). Build verification pending.

### Sparks/Debris (sparks.c) — DONE (Wave 1)
5 functions renamed: `spark_gt_state_init`, `spark_init_all`, `spark_submit_occluded`, `spark_frame_update` (NON_MATCHING), `spark_spawn`. 2 structs: `SparkParticle`, `SparkInstance`. 5 globals: `sSparkTriangleDef`, `sSparkInstances[4]`, `sSparkActive[4]`, `sSparkEmptyBatch`, `sSparkInitDl`. Updated rsp.c (3 sites), combat.c (1), functions.h (1), symbol_addrs.txt (3). Build verification pending.

### Trail Afterimage (trail.c) — DONE (Wave 1)
9 functions renamed: `ringbuf_init`, `ringbuf_push`, `ringbuf_pop`, `spline_init`, `spline_compute`, `spline_add_point`, `spline_get_point`, `trail_gt_init`, `trail_update`. 9 globals renamed: `sTriStrip4_0..3`, `sTriStrip5_0..4`, `sTriStripLong[]`, `sTriStripShort[]`, `sCatmullRomBasis`, `sTrailDl[4]`. Updated functions.h (2 decls), player.c (4 call sites), cam_follow.c (16 init sites). Build verified.

### HUD (hud.c) — DONE (Wave 1)
32 functions renamed (20 HUD + 12 Results): `hud_dust_fade_cb`, `hud_dust_fast_fade_cb`, `hud_bone_to_world`, `hud_circular_offset`, `hud_dust_spawn_cb`, `hud_dust_spawner`, `hud_dust_follow_player`, `hud_dust_sp3_init`, `hud_dust_ring_spawn`, `hud_dust_line_spawn`, `hud_ko_countdown`, `hud_health_width`, `hud_quad_submit`, `hud_health_bar_update`, `hud_round_win_anim`, `hud_timer_cb`, `hud_timer_start`, `hud_score_cleanup`, `hud_score_create`, `hud_setup`, `results_ko_fade`, `results_final_fade`, `results_attract_skip`, `results_wait_timer`, `results_p1_control_skip`, `results_p1_control_continue`, `results_show_controls`, `results_p1_controls_hint`, `results_p1_pause`, `results_fade_in`, `results_init`, `results_portrait_flicker`. 23 globals renamed. Updated functions.h (5 decls), menu.c (3 externs + calls), match.c (~30 refs), player.c (2 refs), cam_follow.c (3), combat.c (2), projectile.c (4), eff_hit.c (3), present.c (3), pregame.c (4), fighters.c (1 array entry). Build verified.

### Presentation Screens (present.c) — DONE (Wave 1)
27 functions renamed: `present_set_screen`, `attract_blink_cb`, `attract_menu_input`, `present_single_win`, `present_attract_cycle`, `present_title_task`, `present_attract_loop`, `present_skip_to_attract`, `present_digi_element`, `present_kronos_fade_out`, `present_kronos_fade_in`, `present_kronos_logo`, `present_title_open_anim`, `present_title_sfx`, `present_title_open`, `present_haze_anim`, `present_haze_init`, `present_theend_skip`, `present_theend_anim_end`, `present_theend_init`, `present_transition_screen`, `present_win_fade_out`, `present_win_result_loop`, `present_winner_wait`, `present_result_timer`, `present_intro_presents`, `present_demo_action`, `present_demo_sfx`. 9 globals + 1 type renamed. Updated functions.h (1 decl), menu.c (2 externs), match.c (2 calls), pregame.c (2 calls). Build verified.

### Selection UI (select.c) — DONE (Wave 1)
21 functions renamed (12 Options + 3 Char Select + 2 Stage Select + 4 Score): `options_input_handler`, `options_menu_task`, `option_game_mode`, `option_round_count`, `option_rounds_win`, `option_sound_mute`, `option_bgm_volume`, `option_sfx_volume`, `option_controller_setup`, `option_char_config`, `option_stage_select`, `option_back_attract`, `select_char_input`, `select_char_update`, `select_char_task`, `select_stage_task`, `select_stage_screen`, `select_score_confirm`, `select_digit_render`, `select_score_display`, `select_score_init`. 10 globals renamed. Updated functions.h (1 decl), menu.c (15 extern decls + ~30 call sites). Build verified.

### Player Init (ply_init.c) — DONE (Wave 1)
1 function: `ply_collect_textures`. Updated functions.h (1 decl), player.c (1 call site). Build verified.

### AI Brain (aibrain.c) — DONE (Wave 1)
37 functions renamed (15 core AI engine + 16 tactic table + 6 extra callbacks). 9 globals renamed (sAiDelayTable, sAiRandDelayTable, sAiAttemptCapTable, sAiTimerBaseTable, sAiInterruptBaseTable, sAiInterruptRandTable, sAiOpenWindowTable, sAiCloseWindowTable, sAiTacticTable). 1 enum (AiReactionFlag) + 1 struct (AiCandidate) renamed. Updated functions.h (5 decls), player.c (7 call sites), eff_hit.c (2 decls + 2 refs), symbol_addrs.txt (3 entries), nonmatching .s file renamed. Build verified.

### Menu (menu.c) — DONE (Wave 1)
48 functions renamed (11 arena stages, 10 char intros, 9 boss/ending, 5 title/logo, 4 options, 5 transitions, 4 fight init, 6 misc callbacks). 16 BSS globals renamed (sFightLocked, sFirstFight, sMenuState, gFighterDistance, sIntroPlayerObjs[2]). Updated functions.h (3 decls), present.c (2 call sites). Build verified.

### Match (match.c) — DONE (Wave 1)
38 functions renamed (4 round flow, 8 KO detection, 7 post-round, 6 result callbacks, 6 UI model helpers, 5 anim callbacks, 2 misc). 6 BSS globals renamed (sWinnerMsgObj, sDrawMsgObj, sKoMsgObj, sAfterKoMsgObj, sContinueMsgObj, sSuddenDeathMsgObj). Updated functions.h (3 decls), callers in cam_follow.c, player.c, main.c, eff_hit.c, fighters.c. Build verified.

### Background (background.c) — NEXT (Wave 1)
Tiled scrolling background (.pcl + .GMD, frustum cull).

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
