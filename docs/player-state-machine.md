# Dark Rift — Player State Machine

## Overview

Each player character is driven by an FSM loaded from a `.db` file per character.
The system has four key layers that nest inside one another:

```
MOVE_ID  →  moveToLogicStateMap  →  LOGIC STATE (FSM index)
                                        │
                                        ├── logicStateTable[even] = TransitionRule ID
                                        │       └── TransitionRule → Behavior + CombatState + Timing
                                        │
                                        └── logicStateTable[odd]  = next lookupLogicTable
```

## Data Structures

### 1. `CombatState` (line 503, common_structs.h)

Per-frame data for each combat action (punch, kick, jump, block, etc.).
Loaded from the `.db` file as a contiguous array indexed by `combatStateId`.

| Offset | Field | Type | Meaning |
|--------|-------|------|---------|
| 0x00 | `minFrame` | s16 | First frame of the state (startup) |
| 0x02 | `maxFrame` | s16 | Last frame of the state (recovery end) |
| 0x04 | `hitboxActiveStart` | s16 | First frame where hitbox is active |
| 0x06 | `hitboxActiveEnd` | s16 | Last frame where hitbox is active |
| 0x08 | `animationId` | s16 | Index into `modInst->animations[]` |
| 0x0A | `hitStanding` | s16 | Move ID for standing hit reaction |
| 0x0C | `hitCrouch` | s16 | Move ID for crouching hit reaction |
| 0x0E | `blockStanding` | s16 | Move ID for standing block reaction |
| 0x10 | `blockCrouch` | s16 | Move ID for crouching block reaction |
| 0x12 | `hitAirborne` | s16 | Move ID for airborne hit reaction |
| 0x14 | `hitJuggle` | s16 | Move ID for juggle hit reaction |
| 0x16 | `hitBackStanding` | s16 | Move ID for back-hit standing reaction |
| 0x18 | `hitBackCrouch` | s16 | Move ID for back-hit crouching reaction |
| 0x1A | `hitBackAirborne` | s16 | Move ID for back-hit airborne reaction |
| 0x1C | `hitMove10` | s16 | Move ID for launcher hit reaction (CSF_10000) |
| 0x1E | `unk_1E` | s16 | Unknown — used in slam face-up/down |
| 0x20 | `damage` | s16 | Base damage dealt by this state |
| 0x22 | `soundTableIndex` | s16 | Index into AnimationSoundTriggers |
| 0x24 | `trailStart` | s16 | First frame of motion trail (-1 = auto) |
| 0x26 | `trailEnd` | s16 | Last frame of motion trail (-1 = auto) |
| 0x28 | `projBarrage` | s16 | Projectile barrage index (-1 = none) |
| 0x2A | `unk_2A` | s16 | Unknown |
| 0x2C | `cutsceneId` | s16 | Combat state index for camera cutscene (-1 = none) |
| 0x2E | `custsceneDelay` | s16 | Cutscene delay frame (-1 = immediate) |
| 0x30 | `unk_30` | s16 | Unknown |
| 0x32 | `unk_32` | s16 | Unknown |
| 0x34 | `flags` | u32 | CSF_* bitmask |

### 2. `TransitionRule` (line 454, common_structs.h)

Defines what input/timing condition causes a transition, and where it leads.

| Offset | Field | Type | Meaning |
|--------|-------|------|---------|
| 0x00 | `timingIndex` | s16 | Index into `transitionTimingTable` |
| 0x02 | `requiredButtons` | u16 | Button input to match (masked by `button_mask`) |
| 0x04 | `flags` | u16 | TRANSITION_FLAG_* bitmask |
| 0x06 | `unk_06` | u16 | Unknown |
| 0x08 | `behaviorId` | s16 | Index into `behaviorTable` |
| 0x0A | `targetStateId` | s16 | Target `combatStateId` (-1 = no change) |
| 0x0C | `button_mask` | u16 | Mask applied to buttons before comparison |
| 0x0E | `aiResponseForChar[11]` | u8 | AI response bias per character |
| 0x19 | `aiSelfStrategy` | u8 | AI strategy for self |
| 0x1A | `pad_1A[2]` | u8 | Padding |

### 3. `TransitionTiming` (line 648, common_structs.h)

Timing parameters for a transition's behavior.

| Offset | Field | Type | Meaning |
|--------|-------|------|---------|
| 0x00 | `unk_00` | s16 | Unknown |
| 0x02 | `unk_02` | s16 | Unknown |
| 0x04 | `unk_04` | s16 | Unknown |
| 0x06 | `unk_06` | s16 | Time window for TRANSITION_FLAG_TIMED |
| 0x08 | `unk_08` | s16 | Sets `player->obj->velocity.z` |
| 0x0A | `unk_0C` | s16 | Sets `player->actionTask->start_delay` |
| 0x0E | `moveTimeout` | s16 | Frames until auto-transition timeout |

### 4. `Behavior` (line 533, common_structs.h)

Defines what happens AFTER a transition is taken (shared global table).

| Offset | Field | Type | Meaning |
|--------|-------|------|---------|
| 0x00 | `newFlags` | s32 | PLAYER_FLAG_* to force ON |
| 0x04 | `animFunc` | ObjFunc | Animation task entry function |
| 0x08 | `actionFunc` | ObjFunc | Action task entry function |
| 0x0C | `transitionAllowedFunc` | func | Gate callback (NULL = always allowed) |
| 0x10 | `preserveFlags` | s32 | PLAYER_FLAG_* to preserve from previous behavior |

Flag merge: `player->flags = newFlags | (player->flags & preserveFlags)`

### 5. `FrameTriggerOverride` (line 641, common_structs.h)

Frame-specific overrides that can change the target state mid-animation.

| Offset | Field | Type | Meaning |
|--------|-------|------|---------|
| 0x00 | `stateIdOverride` | s16 | Target state ID for the override |
| 0x02 | `frameIndex` | s16 | Frame at which the override triggers |
| 0x04 | `stateId` | s16 | Source state ID that this override applies to |
| 0x06 | `transitionActionOverride` | s16 | Action function parameter override |

### 6. `StateOverrideIndex` (line 636, common_structs.h)

Per-combat-state index into the override table.

| Offset | Field | Type | Meaning |
|--------|-------|------|---------|
| 0x00 | `overrideTableOffset` | s16 | Offset into `frameTriggerOverrideTable` |
| 0x02 | `numOverrides` | u16 | Number of override entries for this state |

---

## FSM Core: logicStateTable

The central nervous system is the **logicStateTable** — an `s16[]` array organised in **pairs**:

```
┌───────────────────┬───────────────────┐
│  even index (N)   │  odd index (N+1)   │
├───────────────────┼───────────────────┤
│ transitionRuleId  │ nextLookupIndex   │
└───────────────────┴───────────────────┘
```

- `transitionRuleId` — index into `transitionRuleTable`
- `nextLookupIndex` — where the next `player_select_transition` walk starts
- The table is terminated by a negative value at an even position

A **logic state** is simply an even index into this table. `player->currentLogicState` stores the last one used. `player->lookupLogicTable` is the "program counter" — the index where the next walk begins.

**Selection walk** (`player_select_transition`, line 1208):
```
transitionIndex = player->lookupLogicTable

loop:
  if logicStateTable[transitionIndex] < 0 → break
  transitionRule = transitionRuleTable[logicStateTable[transitionIndex]]
  evaluate conditions ordered by TRANSITION_FLAG priority
  transitionIndex += 2
```

---

## Transition Selection Priority

In `player_select_transition`, each pair is evaluated in this order:

### 1. `TRANSITION_FLAG_DEFAULT` (0x2)
Stored as a candidate. Only executed if nothing else matched AND `arg1 == TRUE`.
If combined with `TURN` and `TURN_AWAY`, skips fallback if character is facing opponent.

### 2. `TRANSITION_FLAG_TIMEOUT` (0x8)
Triggered when `autoTransitionTimer <= 0`.
Forces transition with `arg1 = TRUE`.

### 3. `TRANSITION_FLAG_TURN` (0x10) + `TURN_AWAY` (0x800)
Turn-around: character must be facing away from opponent (`PLAYER_FLAG_NOT_FACING_OPP`).
Requires button input.

### 4. `TRANSITION_FLAG_IMMEDIATE` (0x1)
Input match → execute transition immediately. No frame check.

### 5. `TRANSITION_FLAG_LATER` (0x4)
Input match → if current frame < `maxFrame`, defers via `TASK_FLAG_TRIGGER_FRAME`
at `maxFrame - 1`. Handler: `func_800247CC`.

### 6. `TRANSITION_FLAG_HELD` (0x20)
Input match → frame-gated: only at `minFrame` (during recovery) or `maxFrame`.
Otherwise skips.

### 7. `TRANSITION_FLAG_TIMED` (0x40)
Input match → checks `timeSinceTransition <= timingTable[timingIndex].unk_06`.
Only triggers within the time window.

### 8. (No flags)
Input match → execute transition immediately (fallthrough).

---

## `player_make_transition` (line 1053) — Step by Step

Called by `player_select_transition`, `player_apply_move`, `player_force_move`.

```
1.  Resolve: logicState → logicStateTable[even]
              → transitionRuleTable[transitionId]
              → timingIndex, behaviorId, targetStateId

2.  Same-state guard:
    if targetStateId == currentStateId && arg1 == FALSE → cancel state change

3.  Look up Behavior struct from behaviorTable[behaviorId]

4.  Gate check:
    if transitionAllowedFunc != NULL && returns FALSE → abort transition

5.  Record previous transition: player->previousTransition = player->transition

6.  FrameTriggerOverride search:
    Scan stateOverrideIndices[currentStateId] entries.
    If a matching override is found:
      - frameIndex < sp44->frameIndex → defer via TASK_FLAG_TRIGGER_FRAME
      - else → immediate override (disables AI)
    Override passes: animTaskParams[2] = transitionActionOverride,
                              [3] = stateIdOverride,
                              [4] = behavior->actionFunc

7.  Standard setup (no override):
    actionTask->func = behavior->actionFunc
    if targetStateId >= 0:
        animTask->func = anim_change_combat_state
    else:
        animTask->func = behavior->animFunc

8.  State change:
    if targetStateId >= 0:
        animTaskParams[0] = behavior->animFunc
        animTaskParams[1] = combatStateId
        update player->combatStateId
        trigger cutscene if cutsceneId >= 0

9.  Behavior flags:
    player->flags = behavior->newFlags | (player->flags & behavior->preserveFlags)

10. Bookkeeping:
    player->behaviorId = behaviorId
    player->currentTiming = timingTable[timingIndex]
    player->autoTransitionTimer = moveTimeout
    player->lookupLogicTable = logicStateTable[logicState + 1]
    log_transition_state(player)
```

### `arg1` parameter comparison

| Aspect | arg1 = FALSE (input) | arg1 = TRUE (forced/timeout) |
|--------|---------------------|------------------------------|
| Same-state change | Blocked | Allowed |
| Fallback execution | Not executed | Executed |
| Used by | Normal player input | Timer expiry, CPU, replay, forced moves |

---

## Player Flags (`PLAYER_FLAG_*`)

| Flag | Value | Name | Purpose |
|------|-------|------|---------|
| 0x001 | `PLAYER_FLAG_1` | — | Unknown |
| 0x008 | `PLAYER_FLAG_NOT_FACING_OPP` | Facing | Character faces away from opponent |
| 0x010 | `PLAYER_FLAG_10` | — | Unknown |
| 0x080 | `PLAYER_FLAG_80` | — | Unknown |
| 0x200 | `PLAYER_FLAG_200` | — | Unknown |
| 0x400 | `PLAYER_FLAG_TRANSITION_LOCKED` | Locked | Input transitions blocked |
| 0x800 | `PLAYER_FLAG_REVERSE` | — | Unknown (used with 0x4000 in held/buffer) |
| 0x1000 | `PLAYER_FLAG_ACTION` | — | Reads `prev_buttons` instead of `buttons` |
| 0x2000 | `PLAYER_FLAG_2000` | — | CPU transition blocker |
| 0x4000 | `PLAYER_FLAG_REVERSE_2` | — | Unknown (used with 0x800 in held) |
| 0x8000 | `PLAYER_FLAG_8000` | — | Unknown |
| 0x10000 | `PLAYER_FLAG_10000` | — | Unknown |
| 0x20000 | `PLAYER_FLAG_20000` | — | Unknown |
| 0x40000 | `PLAYER_FLAG_40000` | — | Preserved across behaviors |
| 0x100000 | `PLAYER_FLAG_GAMEPLAY_LOCKED` | — | CPU idle guard |
| 0x200000 | `PLAYER_FLAG_200000` | — | Unknown |
| 0x400000 | `PLAYER_FLAG_400000` | — | Preserved across behaviors |
| 0x800000 | `PLAYER_FLAG_800000` | — | Replay marking flag |
| 0x1000000 | `PLAYER_FLAG_1000000` | — | Unknown |
| 0x2000000 | `PLAYER_FLAG_SHOOTED` | Shot | Has been shot by projectile |
| 0x4000000 | `PLAYER_FLAG_4000000` | — | Preserved across behaviors |
| 0x8000000 | `PLAYER_FLAG_8000000` | — | Unknown |

---

## Transition Rule Flags (`TRANSITION_FLAG_*`)

| Flag | Value | Name | Behaviour |
|------|-------|------|-----------|
| 0x001 | `TRANSITION_FLAG_IMMEDIATE` | Immediate | Execute on button match, no frame check |
| 0x002 | `TRANSITION_FLAG_DEFAULT` | Fallback | Execute only if no other match (auto-default) |
| 0x004 | `TRANSITION_FLAG_LATER` | Held | Defer to `maxFrame - 1` via frame trigger |
| 0x008 | `TRANSITION_FLAG_TIMEOUT` | Timeout | Execute when `autoTransitionTimer` runs out |
| 0x010 | `TRANSITION_FLAG_TURN` | Turn | Face-toward/away check |
| 0x020 | `TRANSITION_FLAG_HELD` | Buffer | Frame-gated: only at `minFrame` or `maxFrame` |
| 0x040 | `TRANSITION_FLAG_TIMED` | Timed | Time-gated by `timingTable.unk_06` |
| 0x800 | `TRANSITION_FLAG_TURN_AWAY` | TurnAway | Modifier: requires `PLAYER_FLAG_NOT_FACING_OPP` |

---

## Combat State Flags (`CSF_*`)

| Flag | Value | Name | Effect |
|------|-------|------|--------|
| 0x00001 | `CSF_CROUCH` | Crouching | Crouching stance indicator |
| 0x00002 | `CSF_JUMP` | Jumping | Airborne indicator |
| 0x00004 | `CSF_STANDING` | Standing | Standing stance indicator |
| 0x00008 | `CSF_HOP` | Hopping | Short hop indicator |
| 0x00010 | `CSF_ROOT_MOTION` | RootMotion | Animation drives position (`OBJ_FLAG_ROOT_MOTION`) |
| 0x00020 | `CSF_ATTACK_RIGHT_FOOT_1` | RF1 | Right foot attack hitbox type 1 |
| 0x00040 | `CSF_ATTACK_RIGHT_HAND` | RH | Right hand attack hitbox |
| 0x00080 | `CSF_80` | — | Sets `OBJ_FLAG_800000`, `OBJ_FLAG_400000` |
| 0x00100 | `CSF_100` | — | Hit reaction modifier |
| 0x00200 | `CSF_200` | — | Slam face-up/down |
| 0x00400 | `CSF_400` | — | Grounded juggle/slam state |
| 0x00800 | `CSF_ATTACK_LEFT_FOOT` | LF | Left foot attack hitbox |
| 0x01000 | `CSF_ATTACK_RIGHT_FOOT_2` | RF2 | Right foot attack hitbox type 2 |
| 0x02000 | `CSF_ATTACK_LEFT_HAND` | LH | Left hand attack hitbox |
| 0x04000 | `CSF_BLOCK` | Block | Blocking state |
| 0x08000 | `CSF_8000` | — | Sets `OBJ_FLAG_20000` with root motion |
| 0x10000 | `CSF_10000` | — | Launcher hit reaction type |
| 0x20000 | `CSF_JUGGLED` | Juggle | Being juggled in air |
| 0x40000 | `CSF_INVINSIBLE` | Invincible | Takes no damage (typo in source) |
| 0x80000 | `CSF_80000` | — | Unused? |
| 0x100000 | `CSF_100000` | — | Unused? |
| 0x200000 | `CSF_200000` | — | Sets `OBJ_FLAG_100000` |

---

## End-to-End Flow

```
Every frame — player_update()
│
├─ 1. Auto-transition timer countdown
│     if timer hits 0 → player_select_transition(player, TRUE)
│
├─ 2. Input transition check
│     if pendingInput && lookupLogicTable >= 0
│        && not in trigger frame
│        && not transition-locked
│     → player_select_transition(player, FALSE)
│
└─ 3. Reset allowTransition for next frame


player_select_transition(player, arg1)
│
├─ Walk logicStateTable from lookupLogicTable
│   Each pair: evaluate TIMEOUT → TURN → IMMEDIATE → HELD → BUFFER → TIMED
│   Store FALLBACK candidates
│
└─ If nothing matched and arg1==TRUE → execute fallback


player_make_transition(player, arg1, logicState)
│
├─ Map logicState → TransitionRule → Behavior + CombatState + Timing
├─ Check gate callback
├─ Handle frame trigger overrides
├─ Set actionTask + animTask functions
├─ Update combatStateId, behaviorId, flags
├─ Seed lookupLogicTable for next frame
└─ Record transition snapshot for replay
```

## Data Dependency Summary

```
.db file  ──→  logicStateTable[]         pairs of (transitionId, nextLookup)
            │
            ├─→ transitionRuleTable[]    maps input/timing → behavior + state
            ├─→ combatStateTable[]       per-frame combat data (damage, hitboxes, etc.)
            ├─→ transitionTimingTable[]  timing params (moveTimeout, delays)
            ├─→ behaviorTable[]          global shared table (gBehaviorTable)
            ├─→ stateOverrideIndices[]   per-state → override offset + count
            ├─→ frameTriggerOverrideTable[]
            ├─→ moveToLogicStateMap[]    MOVE_ID → logicState
            └─→ soundTable[]             AnimationSoundTriggers

Global constants:
  gBehaviorTable[] — shared Behavior table (58 entries)
  D_8004B94C[] — MOV file prefix table (11 characters × 2 variants)
```
