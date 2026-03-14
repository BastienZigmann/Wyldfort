# Wyldfort — Game Specification (v1)

**Document purpose**  
This document defines the initial playable specification for *Wyldfort* and the intended architecture direction for an Unreal Engine (latest version) C++ project. It aims to prevent scope drift by clearly stating pillars, scope, systems, data, and phased development goals (POC-first).

**Project intent**  
A dark-fantasy, 3D, free-placement city builder focused on **defense management** under **fog-of-war**. The player primarily manages the settlement indirectly (policies, buildings, missions), not by micro-controlling individuals.

---

## 1. High-level concept

### 1.1 One-sentence pitch
A 3D dark-fantasy city builder where you grow a settlement on a procedurally generated map under RTS-style fog-of-war, while surviving escalating threats using villagers, a standing guard, and an adventurers guild that runs missions for scouting, combat, and exploration.

### 1.2 Core pillars
1. **Defense management is central**: threats escalate with settlement growth and discovery.
2. **Indirect control**: the player does not command NPCs individually in real time; instead they assign via buildings/UIs (and later policies/roles).
3. **Exploration and uncertainty**: fog-of-war hides resources and threats; discovery persists as “memory.”
4. **Progression through competence**: villagers improve skills by doing; advanced buildings unlock based on competence thresholds.
5. **Multiple defense tools**:
   - **Temporary militia** (villagers equipped short-term; weak).
   - **Trained guards** (reliable, recruited from newcomers).
   - **Adventurers** (guild-based, mission-driven, personality/needs-driven retention).

---

## 2. Target experience

### 2.1 Player actions (moment-to-moment)
- Place buildings freely in 3D.
- Manage resources via inventories/stockpiles and transfers.
- Discover and monitor the world through fog-of-war reveal.
- React to threats: spot scouts, decide whether to patrol, send missions, recruit guards, equip militia.
- Grow settlement capabilities through research/crafting unlocked by expedition loot and competence.

### 2.2 Game tone
- Semi dark-fantasy frontier survival.
- Tension from periodic threat escalation and uncertainty beyond explored areas.

---

## 3. Scope and boundaries

### 3.1 In scope for initial production (POC and first playable)
- Procedural map (minimal viable version; can be simplified to “seed + POIs”).
- 3D free placement building with basic validation.
- Fog-of-war with **continuous discovery + persistent memory**.
- Resource gathering and transfer through an **Inventory Component** applicable to many actors.
- Villagers as autonomous agents (high-level), with minimal assignment via building UI (+ button to add worker).
- Threat escalation loop (starting with wolves; later goblins).
- Guards recruited from newcomers (trained unit class).
- Adventurers guild missions (scout/fight/explore) as a major defense tool (can be phased into later milestones if necessary).

### 3.2 Explicitly deferred (not required early)
- Roads and advanced pathfinding/traffic simulation.
- Highly detailed tactical combat or animation-driven combat.
- Deep social simulation (relationships, family trees, etc.).
- Large tech trees and complex crafting chains.
- Fully simulated logistics at per-item granularity for all NPCs.

---

## 4. World & camera

### 4.1 Camera (3D city builder)
- RTS-like camera:
  - pan
  - zoom
  - rotate
- Selection:
  - click to select building/NPC (POC: buildings first)
- Build mode:
  - building preview (“ghost”), confirm/cancel

### 4.2 Map generation (minimal)
**POC minimum**:
- A playable area containing:
  - spawn region suitable for early building (relatively flat)
  - nearby resource zones
  - at least one threat source/den
  - at least one “unknown POI” for exploration (later can be goblin camp)

---

## 5. Fog-of-war (RTS-style with memory)

### 5.1 Desired behavior
- **Continuous discovery**: as scouts/units/buildings reveal areas, the fog recedes in real time.
- **Freeze after leaving**: once an area is out of vision, the player retains the last known state.
- **Memory**: the map displays “last known info,” but if something changed while unseen, it is only updated when re-scouted.

### 5.2 Terms
- **Visible**: currently in sight (true state shown).
- **Remembered**: explored previously but not currently visible (cached/last known state shown).
- **Unexplored**: never seen (hidden).

### 5.3 POC simplification
- First implementation can be:
  - Visibility computed from sources (watchtowers, scouts) as circles projected on ground plane.
  - Memory stores:
    - explored flag
    - last known presence of POIs/threat markers (not necessarily exact composition)
  - When re-entering vision, refresh state.

---

## 6. Resources & inventories

### 6.1 Core resource model
- Resources have:
  - `ResourceId` (e.g., Food, Wood, Stone, Gold)
  - quantity (integer for POC)

### 6.2 Inventory Component (existing direction)
A reusable **Inventory Component** enabling any actor to:
- store a set of resources (by type)
- receive resources
- transfer resources to another inventory
- enforce capacity rules if needed

**Design intent**:
- Stockpiles, warehouses, caravans, villagers, buildings can share the same inventory logic.

### 6.3 Transfer rules (POC)
- Transfers are explicit actions (e.g., “Send X wood from Stockpile A to Building B”).
- Automation (carriers/logistics AI) is later.

---

## 7. Buildings (free placement)

### 7.1 Placement validation (POC)
A building can be placed if:
- not overlapping another building (simple collision check)
- slope under a threshold (optional POC; can start with flat starting area)
- within “settlement influence” radius from Town Center (prevents random distant outposts early)

### 7.2 Building interaction UI
- Clicking a building opens its UI panel.
- POC worker assignment:
  - a `+` button adds a worker slot / requests a villager assignment
  - (Later) this evolves into quotas/priorities/policies.

### 7.3 Minimal building set (suggested initial)
- Town Center (core influence, starting point)
- House (population capacity)
- Stockpile (inventory storage)
- Food source building (Forager Hut or Farm)
- Wood source building (Lumber Camp)
- Watchtower (visibility)
- Guild Hall (adventurer roster + mission board)
- Guard Barracks / Guard Post (train guards, assign guards)

---

## 8. NPCs and control model

### 8.1 General NPC rule
NPCs manage themselves; the player interacts via:
- building UIs (assign worker slots)
- equipment assignment (for militia/guards/adventurers)
- mission assignment (guild board)
- later: policies and global job priorities

### 8.2 Villagers
Villagers are:
- workforce
- can be temporarily equipped as militia but are weak

POC needs (minimal):
- Food consumption (global/settlement-level is acceptable for POC)
- Rest/day-night schedule (simplified)

Skills (POC):
- Gathering
- Building
- Combat (militia baseline low)

### 8.3 Guards (trained)
- Guards are recruited from **newcomers**.
- Guards are trained, reliable defenders.
- Guards can be assigned to:
  - guard posts/patrol (later)
  - defend during attacks (POC: global defense rating)

### 8.4 Adventurers (guild)
Adventurers are external/independent actors staying in the guild.
They require:
- rewards (gold/loot)
- comfort/entertainment (POC: single “comfort score”)
- personality affects demands and behavior (POC: 1 trait)

Mission types (initial):
- Scout
- Fight/hunt threat
- Explore POI

---

## 9. Threats and escalation

### 9.1 Threat concept
Threats increase with settlement growth and time:
- early: wolves
- later: goblins (hidden by fog-of-war, discovered via scouting)

### 9.2 Threat lifecycle
- A threat source exists (den/camp/region).
- Scouts may spot signs before an attack (optional POC+).
- Attacks or pressure events occur based on escalation model.
- Player response options:
  - militia defense (weak)
  - guard defense (stable)
  - adventurer mission (high leverage but requires management)

### 9.3 Combat model (POC)
- Combat resolved by **numbers** (no tactical simulation).
- Inputs:
  - attacker strength
  - defender strength (militia + guards + adventurers on mission)
  - modifiers: time (night), equipment, skill, trait
- Outputs:
  - casualties/injuries (simple)
  - building damage (optional POC+)
  - loot/reward

**Debug requirement**:
- combat resolution produces a log entry explaining why outcomes happened.

---

## 10. Progression: competence, unlocking, research/crafting

### 10.1 Competence unlocking
Villagers gain skill by performing tasks.
Some buildings require:
- a minimum competence level in a relevant skill.

Example:
- Workshop requires Building Skill >= 2
- Advanced Watchtower requires Gathering Skill >= 2 (materials) + Building Skill >= 2

### 10.2 Research/crafting (POC slice)
POC includes:
- minimal research tree (3–5 nodes max)
- 1–3 craftable equipment items affecting combat modifiers

Loot sources:
- missions
- exploration POIs
- threat den clearing

---

## 11. Data & configuration (initial approach)
To avoid overengineering:
- POC can use C++ data tables/structs for definitions.
- Later iteration can migrate to:
  - UE DataAssets
  - JSON (if needed for core lib reuse)

Definitions needed:
- Resource types
- Building definitions (cost, upkeep, output, worker slots)
- NPC archetypes (villager baseline, guard, adventurer)
- Mission definitions
- Threat definitions
- Equipment definitions

---

## 12. Systems list (responsibilities)

### 12.1 Inventory System
- Owns the Inventory Component behavior:
  - add/remove/transfer
  - optional capacity rules
  - (later) reservations and logistics

### 12.2 Building System
- Placement rules and construction lifecycle:
  - preview, validate, place
  - construction cost deduction (from relevant inventory)
  - worker slots and assignment requests

### 12.3 Population System
- Tracks villagers, newcomers, housing capacity.
- Spawns newcomers over time or via events (POC: simple).

### 12.4 Work Assignment System (POC minimal)
- Building UI requests workers (`+`).
- System assigns available villager to that building role.
- No advanced job selection/policies yet.

### 12.5 Visibility/Fog System
- Maintains:
  - current visibility
  - explored memory
  - last known states for discovered POIs/threats

### 12.6 Threat System
- Threat pressure model
- Spawn/attack scheduling
- Threat sources hidden by fog until discovered

### 12.7 Combat Resolver
- Deterministic-ish numeric combat with logs

### 12.8 Guild/Mission System
- Adventurer roster
- Mission creation, travel time abstraction
- Mission resolution (scout updates fog memory; fight uses combat resolver)
- Rewards/comfort changes

### 12.9 Time System
- Day/night cycle
- Ticks and event scheduling (attacks, consumption, production, mission completion)

---

## 13. Unreal Engine implementation direction (architecture guidance)

### 13.1 Component-oriented, SOLID, KISS
- Prefer:
  - small, focused components (Inventory, Health, VisibilitySource, WorkerProvider, etc.)
  - clear ownership and responsibilities
- Avoid:
  - “God actors” with too many responsibilities
  - prematurely building a full ECS if UE components suffice

### 13.2 Recommended patterns (where appropriate)
- **Facade**: a `GameServices` or `WorldSubsystem` exposing high-level APIs to UI/actors.
- **Command pattern**: player actions as commands (`PlaceBuilding`, `AssignWorker`, `StartMission`).
- **Observer/Event bus**: systems publish events (resource changed, threat discovered, mission completed).
- **State pattern**: missions and NPC states (idle, working, traveling, resting).
- **Factory**: spawning entities/buildings from definitions (DataAssets).

### 13.3 UE features: use vs avoid (early)
Use early:
- Actor Components for modular behaviors (InventoryComponent, VisibilityComponent)
- Subsystems (GameInstanceSubsystem / WorldSubsystem) to centralize simulation services
- DataAssets for definitions (later; structs for POC is fine)
- UMG for building UI panels + mission board

Avoid early:
- Behavior Trees/AI Perception for everything (overkill for POC)
- Complex navigation/roads/pathfinding (explicitly deferred)
- Gameplay Ability System (likely overkill initially)

---

## 14. Development phases (milestones)

### Milestone 1 — “Foundations”
**Goal**: minimal playable loop building + resources.
- Building placement (Town Center, Stockpile, House)
- Inventory Component usable by buildings
- Resource add/remove/transfer
- Simple time tick + day/night indicator

**Acceptance**:
- You can place buildings, store resources, and see them change over time.

### Milestone 2 — “Production & survival”
**Goal**: settlement can sustain itself.
- Food and wood production buildings
- Consumption per day
- Worker assignment via building `+`
- Lose condition: starvation

**Acceptance**:
- You can reach a stable steady-state without threats.

### Milestone 3 — “Fog-of-war with memory”
**Goal**: exploration changes decision-making.
- Watchtower visibility
- “explored vs remembered vs unseen”
- Hidden POI markers that appear only when seen

**Acceptance**:
- You can reveal areas; leaving keeps last known view; re-enter refreshes.

### Milestone 4 — “Threat loop”
**Goal**: the game becomes about defense.
- Wolves threat source
- Threat pressure
- Attack events
- Militia defense (weak) + casualties

**Acceptance**:
- Threat event can be survived/failed; results logged and understandable.

### Milestone 5 — “Guards and guild”
**Goal**: main defenses are online.
- Newcomers recruited into guards
- Guard Post building + defense rating
- Guild Hall + adventurers roster
- Mission board: scout/fight/explore
- Rewards/comfort/trust (POC simple)

**Acceptance**:
- Player can solve threats by dispatching guild missions and/or guards.

### Milestone 6 — “Progression slice”
**Goal**: meaningful improvement over time.
- competence thresholds unlocking 1–2 advanced buildings
- minimal research nodes
- 1–3 craftable items affecting combat

**Acceptance**:
- Player feels a progression and can choose upgrades.

---

## 15. Open decisions (to refine later)
- Exact newcomer rates and guard training pipeline
- Exact resource logistics model (global stockpile vs distributed; initial likely distributed via Inventory Component + stockpiles)
- How missions choose targets (region-based vs POI-based)
- How threat escalation scales with player actions
- Save/load design
- UI layout and information density

---

## 16. Appendix: Notes from previous implementation
- An **Inventory Component** was previously prototyped:
  - goal: any Actor can own an inventory
  - support receive/transfer resources

This should be retained and formalized as a foundational component in the early milestones.

---
End of document.
