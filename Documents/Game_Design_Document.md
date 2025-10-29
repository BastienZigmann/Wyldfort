# GAME DESIGN DOCUMENT

## Project Codename: **Wyldfort**

**Version:** 1.0  
**Last Updated:** 2025-10-02  
**Lead Designer/Developer:** BastienZigmann  
**Engine:** Unreal Engine 5 (C++ focused)  
**Target Platform:** PC (Primary)  
**Genre:** City Builder, Real-Time Strategy, Dark Fantasy Management

---

## TABLE OF CONTENTS

1. [Executive Summary](#executive-summary)
2. [Core Vision & Pillars](#core-vision--pillars)
3. [Gameplay Overview](#gameplay-overview)
4. [Core Gameplay Loop](#core-gameplay-loop)
5. [Game Systems](#game-systems)
6. [Technical Architecture](#technical-architecture)
7. [Content & Progression](#content--progression)
8. [Minimum Viable Product (MVP) Roadmap](#minimum-viable-product-mvp-roadmap)
9. [Missing Pieces & Open Questions](#missing-pieces--open-questions)
10. [Risk Assessment](#risk-assessment)

---

## 1. EXECUTIVE SUMMARY

### High Concept

*"A dark fantasy city builder where you nurture a settlement from a single hut to a fortified city, while managing existential threats through hired adventurers and strategic guild management—not direct combat."*

### Unique Selling Points (USP)

1. **Indirect Combat System** - You don't fight; you hire, equip, and strategically deploy adventurers
2. **Organic Road Formation** - Roads emerge from villager pathways (emergent design)
3. **Autonomous Agent Economy** - Villagers and adventurers act independently based on needs/availability
4. **Threat Management** - Proactive scouting and reactive defense create strategic tension
5. **Relaxed Pace with Stakes** - Foundation-style pacing but with dark fantasy consequences

### Core Audience

- Fans of Foundation, Anno, Banished, RimWorld (lite), They Are Billions
- Players who enjoy strategic planning over twitch reflexes
- Fantasy management game enthusiasts

---

## 2. CORE VISION & PILLARS

### Design Pillars (What Makes This Game Special)

#### Pillar 1: **Organic Growth**

The city should feel alive and emergent. Roads form naturally, villagers create paths, buildings cluster logically. The player guides rather than dictates.

#### Pillar 2: **Indirect Power**

The player is a steward, not a hero. Power comes from preparation, planning, and proper resource allocation—not from sword swinging.

#### Pillar 3: **Meaningful Threats**

Threats aren't just nuisances; they have sources, escalate logically, and require investigation and strategic response.

#### Pillar 4: **Consequence & Persistence**

Adventurers can die permanently. Resources can be lost. Decisions matter, but the game isn't punishingly difficult.

---

## 3. GAMEPLAY OVERVIEW

### Camera & Controls

- **Perspective:** Top-down/Isometric RTS-style camera
- **Camera Controls:** WASD or edge scrolling, mouse wheel zoom, rotate (Q/E)
- **Time Control:** Real-time with pause, slow (0.5x), normal (1x), fast (2x), very fast (4x)
- **Interaction:** Left-click to select, right-click to command/build, drag to area select

### Core Player Activities

1. **Resource Management** - Gather, process, store, and transport resources
2. **City Planning** - Place buildings, optimize logistics, ensure villager needs
3. **Threat Assessment** - Scout areas, identify danger levels, respond appropriately
4. **Guild Management** - Hire adventurers, assign quests, manage risk/reward
5. **Defense Coordination** - Position guards, patrol routes, emergency responses
6. **Economic Development** - Create shops (weapons, magic items) for adventurers and travelers

---

## 4. CORE GAMEPLAY LOOP

### Macro Loop (Long-term, 30+ minutes)

```
Expand Territory → Scout for Threats → Clear Threats with Guild → 
Secure Resources → Build Infrastructure → Attract More Villagers → 
Research/Unlock New Buildings → Face Escalating Threats → REPEAT
```

### Micro Loop (Short-term, 5-15 minutes)

```
Identify Need (food, wood, housing) → Gather Resources → 
Build Production/Storage → Villagers Fulfill Jobs → 
Monitor for Threats → Respond if Needed → Check Guild Status → REPEAT
```

### Session Loop (Single Play Session)

```
Load Game → Check City Status → Address Immediate Needs → 
Set Long-term Goals → Work Toward Goals → Respond to Events → 
Save & Exit
```

---

## 5. GAME SYSTEMS

### 5.1 RESOURCE SYSTEM

#### Primary Resources (Tier 1)

- **Wood** - Harvested from trees by lumberjacks
- **Stone** - Gathered from rocks/quarries by miners
- **Food** - Farms (wheat, vegetables), hunting, fishing
- **Water** - Wells, rivers (for villager needs)

#### Processed Resources (Tier 2)

- **Planks** - Wood → Sawmill → Planks (used in advanced buildings)
- **Bricks/Blocks** - Stone → Mason → Bricks (fortifications, walls)
- **Processed Food** - Raw food → Bakery/Kitchen → Meals (better satisfaction)
- **Leather** - Hunting → Tanner → Leather (for armor crafting)

#### Advanced Resources (Tier 3) - **[TBD: Expand in later phases]**

- **Iron Ore** → **Iron Ingots** → Weapons/Tools
- **Magical Components** - From cleared dungeons/monsters
- **Cloth/Textiles** - From farms (flax) or traders
- **Gold/Currency** - Trade, taxes, quest rewards

#### Resource Properties

- **Weight/Volume** - Affects transport time and storage requirements
- **Perishability** - Food spoils if not stored properly (future feature)
- **Rarity** - Common (wood) → Rare (magical components)

#### Transport System

- **Manual Transport:** Villagers carry resources point-to-point
- **Cart Transport:** (Future) Faster bulk transport
- **Escort Requirement:** In unsafe areas, resources need soldier/adventurer escort
- **Production Batching:** Resources produce in large batches infrequently (reduces micro, increases stakes)

---

### 5.2 BUILDING SYSTEM

#### Building Categories

**Housing & Population**

- **Tent/Hut** - Starting shelter (houses 1-2)
- **Small House** - Basic housing (houses 4)
- **Family Home** - Mid-tier (houses 6)
- **Townhouse** - Late-game (houses 8-10)

**Resource Production**

- **Lumberjack Camp** - Wood production
- **Quarry** - Stone production
- **Farm** - Food production (wheat, vegetables)
- **Hunting Lodge** - Meat/leather production
- **Fishing Hut** - Fish production

**Processing Buildings**

- **Sawmill** - Wood → Planks
- **Mason Workshop** - Stone → Bricks
- **Bakery** - Raw food → Meals
- **Tannery** - Animal parts → Leather

**Storage**

- **Stockpile (Open)** - Basic resource storage
- **Warehouse** - Protected, larger capacity
- **Granary** - Food-specific storage

**Defense**

- **Guard Tower** - Houses guards, provides vision
- **Barracks** - Trains and houses soldiers
- **Walls & Gates** - Physical barriers
- **Patrol Routes** - Assignable routes for guards

**Guild & Combat Support**

- **Guild Hall** - Core adventurer hub (quest board, lodging)
- **Weapon Shop** - Produces/sells weapons (autonomous adventurer purchasing)
- **Magic Shop** - Produces/sells magic items
- **Training Grounds** - Adventurers can train when idle
- **Infirmary** - Healing for wounded adventurers/soldiers

**Villager Needs**

- **Well** - Water supply
- **Tavern** - Social gathering, happiness
- **Market** - General goods, trade with travelers
- **Chapel/Temple** - Religious needs (future)

**Research & Advancement** - **[DESIGN TBD]**

- **Architect's Office** - Unlocks building types
- **Alchemist Lab** - Researches potions, magic
- **Library** - General research hub
- **Strategy Room** - Military/tactical research

#### Building Placement System

- **Phase 1 (MVP):** Grid-based or free placement, simple collision
- **Phase 2 (Post-MVP):** Roads form organically from villager pathing
- **Terrain Considerations:** Flat ground, slopes, water proximity
- **Proximity Bonuses:** Buildings near related structures get efficiency boosts

---

### 5.3 VILLAGER SYSTEM

#### Villager Attributes

- **Name** - Procedurally generated
- **Age** - Child, Adult, Elder (affects work capacity)
- **Job** - Lumberjack, Farmer, Builder, etc.
- **Needs** - Food, Water, Shelter, Happiness
- **Status** - Idle, Working, Sleeping, Eating, Socializing

#### Villager Needs (Foundation/Anno-style, not RimWorld deep)

- **Food:** Must eat periodically
- **Water:** Needs access to well/water source
- **Shelter:** Must have assigned housing
- **Happiness:** Affected by taverns, events, threats
- **Work:** Villagers automatically take jobs based on building assignments

#### Villager Behavior (Autonomous Agents)

1. **Job Assignment:** Player assigns job slots to buildings (e.g., "Lumberjack Camp: 2 workers")
2. **Autonomous Scheduling:** Villagers work, eat, sleep, socialize on their own
3. **Pathfinding:** Villagers create paths → paths become roads (organic system)
4. **Needs Prioritization:** Will prioritize survival needs over work

#### Population Growth

- **Natural Growth:** Villagers reproduce over time if happy and housed
- **Immigration:** Travelers can be convinced to settle (requires housing, happiness)
- **Growth Unlocks:** More population → more building options → more threats

---

### 5.4 GUILD & ADVENTURER SYSTEM

#### Guild Hall Mechanics

- **Quest Board:** Player posts quests (clear dungeon, escort caravan, patrol area)
- **Adventurer Pool:** Available adventurers visible with stats
- **Hiring:** Pay upfront cost to hire adventurer (permanent until death)
- **Emergency Quests:** Rush quests during attacks (higher cost, faster response)

#### Adventurer Attributes

- **Name & Portrait**
- **Level:** 1-20+ (increases with successful quests)
- **Class:** Tank, Damage Dealer (DD), Healer, Support
- **Rank:** S / A / B / C / D (or numerical level, TBD)
- **Health/Status:** Healthy, Injured, Dead (permadeath)
- **Gear Quality:** Poor → Legendary (if they purchase from shops)

#### Adventurer Behavior (Autonomous Agents)

- **Free Will:** Adventurers accept/decline quests based on difficulty, reward, their level
- **Gear Purchasing:** Will visit weapon/magic shops if available and if they have gold
- **Downtime:** Train at training grounds, rest at tavern, heal at infirmary
- **Company Formation:** Adventurers organize into parties (balanced comp preferred)

#### Quest Types

1. **Area Clearance:** "Clear goblin camp in Forest West" (removes threat source)
2. **Escort Mission:** Protect resource transport through dangerous area
3. **Scouting:** Send scouts (separate from adventurers?) to reveal threat levels
4. **Boss Hunt:** High-level quest to eliminate major threat
5. **Defense Quest:** Emergency response during active attack

#### Quest Difficulty Rating

- **Player's Responsibility:** You rate quest difficulty (Easy/Medium/Hard/Deadly)
- **Scouting Impact:** Send scouts first → get accurate difficulty rating
- **Poor Rating = High Risk:** Misrate a quest, adventurers may die
- **Accurate Rating:** Adventurers more likely to accept and succeed

#### Permadeath & Consequences

- **Dead Adventurers:** Permanently lost, gear lost (or recoverable as loot?)
- **Injured Adventurers:** Must heal at infirmary (time-based)
- **Morale Impact:** Losing adventurers affects guild reputation (future feature?)

---

### 5.5 THREAT & COMBAT SYSTEM

#### Threat Types

- **Wildlife:** Wolves, bears (low threat, early game)
- **Bandits:** Human raiders (target resources, villagers)
- **Monster Camps:** Goblins, orcs (escalating threat if not cleared)
- **Dark Magic Users:** Necromancers, cultists (summon undead, curses)
- **End-Game Boss:** "The Scourge" or major foe (late-game climax)

#### Threat Mechanics

- **Threat Sources:** Most threats have a source (camp, dungeon, lair)
- **Escalation:** Ignoring sources leads to larger, more frequent attacks
- **Attack Triggers:** Random chance + proximity + time since last attack
- **Attack Targets:** Villagers, resource stockpiles, buildings

#### Threat Detection

- **Visual Hints:** Smoke from camps, shadowy figures, dead trees (dark magic)
- **Guard Patrols:** Soldiers on patrol can spot threats, alert player
- **Scout Reports:** Dedicated scout units provide detailed info
- **Difficulty Settings:**
  - **Easy:** Threats marked on map with icons
  - **Medium:** Visual hints only, player must investigate
  - **Hard:** No assistance, pure observation required

#### Defense Options

**Option 1: Soldiers (Low Power, Always Available)**

- Trained at barracks
- Patrol routes or guard posts
- Can handle basic threats (wildlife, small bandit groups)
- **Do NOT send against high-level threats** (will die)

**Option 2: Adventurers (High Power, Quest-Based)**

- Hired from guild
- Send on clearance quests to remove threat sources
- Can handle mid-to-high level threats
- Risk permadeath if quest misrated

**Option 3: Kingdom Aid (Safety Net)**

- Call for help from the kingdom (limited uses per game year?)
- External army arrives to help with overwhelming threats
- Essential for early game, rare use late game
- Costs reputation or gold (TBD)

**Option 4: Advanced Military (Late Game, TBD)**

- **Elite Battalions:** Hire specialized units (battle mages, knights)
- Higher cost, higher power than basic soldiers
- Bridge gap between soldiers and adventurers

#### Combat Resolution

- **Player Does Not Control Combat Directly**
- **Automated Resolution:** System calculates outcome based on:
  - Attacker strength vs. Defender strength
  - Gear quality, levels, class composition
  - Environmental factors (walls, chokepoints)
- **Player Watches or Sees Results:** Visual feedback (battle animations) or text log
- **Outcome:** Victory, defeat, partial success (some losses)

---

### 5.6 TRAVELER & ECONOMY SYSTEM

#### Travelers

- **Random Visitors:** NPCs pass through your city periodically
- **Purchasing:** Buy items from your shops (weapons, magic items, food)
- **Recruitment:** Player can attempt to convince travelers to settle
  - **Requirements:** Available housing, high happiness, perhaps gold cost
- **Quest Givers (Future):** Travelers might offer side quests or trade deals

#### Economy & Currency

- **Gold Sources:**
  - Taxes from villagers (automatic, slow income)
  - Sales from shops (adventurers/travelers purchasing)
  - Quest rewards (if quests generate loot/gold)
  - Trade with external merchants (future)
- **Gold Sinks:**
  - Hiring adventurers
  - Building construction
  - Soldier wages
  - Kingdom aid
  - Research costs (if implemented)

#### Shop Mechanics (Weapon/Magic Shops)

- **Production:** Shops produce items using resources (iron → swords, components → potions)
- **Inventory:** Limited slots, items visible
- **Autonomous Purchasing:** Adventurers/travelers browse and buy if interested and have gold
- **Pricing:** Player sets prices? Or auto-balanced by game? **(TBD)**

---

### 5.7 PROGRESSION SYSTEM

#### City Development Stages

1. **Settlement (Pop: 1-10)** - Single hut, basic survival
2. **Hamlet (Pop: 10-30)** - Small cluster, first walls, basic guild
3. **Village (Pop: 30-100)** - Established economy, regular threats
4. **Town (Pop: 100-300)** - Advanced buildings, multiple adventurer companies
5. **City (Pop: 300+)** - Full walls, elite defenses, end-game threats

#### Unlocking New Content

**Option A: Research Tree (Building-Based)**

- Build "Architect's Office" → unlocks research options
- Research categories: Architecture, Military, Magic, Economy
- Costs: Gold + Time + perhaps resources
- Example: Research "Stone Walls" → unlocks Wall building

**Option B: Milestone-Based**

- Reaching population thresholds unlocks buildings
- Clearing threat sources unlocks advanced guild options
- Simpler, less micromanagement

**Option C: Hybrid (Recommended for MVP)**

- Most buildings unlock via population milestones
- A few special buildings (advanced military, magic) require research

#### Adventurer Progression

- **Experience Gain:** Completing quests grants XP
- **Leveling Up:** Increases stats (HP, damage, defense)
- **Gear Progression:** Adventurers purchase better gear from shops
- **Company Prestige (Future):** High-level companies attract better recruits

---

### 5.8 UI/UX SYSTEMS

#### HUD Elements

- **Top Bar:**
  - Population count
  - Resource counts (wood, stone, food, gold)
  - Threat alert icon (flashes when attack incoming)
  - Time controls (pause, 0.5x, 1x, 2x, 4x)
- **Bottom Left:**
  - Building menu (categorized tabs)
  - Current selection info (building stats, villager info)
- **Bottom Right:**
  - Guild panel (adventurer list, quest board)
  - Minimap with threat indicators
- **Notifications:**
  - Pop-up messages for key events (attack, quest complete, villager death)

#### Key Panels

- **Building Menu:** Categorized tabs (Housing, Production, Defense, Guild, etc.)
- **Guild Panel:** 
  - Adventurer roster (portraits, levels, status)
  - Quest board (active quests, available quests)
  - Emergency quest button
- **Resource Panel:** Detailed resource flow, storage capacity
- **Threat Map:** Overlay showing known threats, patrol routes, guard coverage

---

## 6. TECHNICAL ARCHITECTURE

### 6.1 CORE SYSTEMS (C++ Focus)

#### Entity Component System (ECS) Approach

- **Entities:** Villagers, Adventurers, Soldiers, Buildings, Threats
- **Components:** Health, Inventory, Needs, JobAssignment, Location, etc.
- **Systems:** PathfindingSystem, CombatSystem, NeedsSystem, ProductionSystem

#### Key Systems to Implement

**1. PathfindingSystem**

- **Tech:** A* or NavMesh-based pathfinding
- **Challenge:** Hundreds of villagers pathfinding simultaneously
- **Optimization:** Path caching, hierarchical pathfinding, path smoothing
- **Road Formation:** Track frequently used paths, generate road meshes

**2. Agent AI System**

- **Behavior Trees or Utility AI** for decision-making
- **Villagers:** Prioritize needs → find job → work → return home
- **Adventurers:** Accept quests → gear up → travel → execute → return
- **Threats:** Spawn → move toward city → attack → retreat or die

**3. Combat Resolution System**

- **Turn-based under the hood** but presented as real-time
- **Stat-based calculation:** Attack vs. Defense, HP pools, damage rolls
- **Class synergy:** Healers heal, tanks absorb damage, DDs deal damage
- **No player input during combat** (automated)

**4. Production & Economy System**

- **Job Slot System:** Buildings have slots, villagers fill slots
- **Production Queue:** Sawmill produces planks in batches
- **Resource Transport:** Assign transport jobs to villagers
- **Shop System:** Inventory management, autonomous purchasing AI

**5. Event & Threat System**

- **Threat Spawner:** Periodically spawns threats based on:
  - Time since last attack
  - Uncleared threat sources
  - City development level
- **Escalation Manager:** Tracks ignored threats, increases frequency/difficulty
- **Detection System:** Raycasts for visual hints, guard proximity checks

**6. Save/Load System**

- **Serialization:** Save world state (buildings, villagers, adventurers, resources)
- **Autosave:** Every X minutes
- **Multiple Save Slots**

---

### 6.2 UNREAL ENGINE SPECIFIC

#### Asset Structure

```
Content/
├── Core/
│   ├── Blueprints/
│   │   ├── GameMode/
│   │   ├── PlayerController/
│   │   └── UI/
│   └── Data/
│       ├── BuildingData/
│       ├── ResourceData/
│       └── ThreatData/
├── Environment/
│   ├── Terrain/
│   ├── Buildings/
│   ├── Props/
│   └── Nature/
├── Characters/
│   ├── Villagers/
│   ├── Adventurers/
│   ├── Soldiers/
│   └── Threats/
└── UI/
    ├── HUD/
    ├── Menus/
    └── Icons/
```

#### Core Classes (C++)

**AMyGameMode**

- Manages game state, spawning, difficulty settings

**AMyPlayerController**

- Handles camera, input, UI interaction

**UBuildingComponent**

- Attached to building actors, manages production, workers

**AVillagerCharacter**

- Villager entity, AI controller, needs system

**AAdventurerCharacter**

- Adventurer entity, quest handling, combat stats

**UThreatManager**

- Spawns and manages threats, escalation logic

**UGuildSystem**

- Quest board, adventurer hiring, quest assignment

**UResourceManager**

- Tracks global resources, storage, transport

---

### 6.3 PERFORMANCE CONSIDERATIONS

#### Optimization Strategies

1. **LOD for Characters:** Use LODs for villagers/adventurers at distance
2. **Instanced Static Meshes:** For trees, rocks, buildings
3. **Occlusion Culling:** Hide buildings/characters behind other structures
4. **AI Throttling:** Update AI at lower frequency (every 0.5s instead of per frame)
5. **Pathfinding Budget:** Limit pathfinding queries per frame
6. **Object Pooling:** Reuse character/threat actors instead of spawning/destroying

#### Target Performance

- **60 FPS** on mid-range PC (GTX 1660 / Ryzen 5 3600)
- **200+ villagers** on screen without major slowdown
- **50+ adventurers** active simultaneously

---

## 7. CONTENT & PROGRESSION

### 7.1 BUILDING PROGRESSION

#### Early Game (Settlement → Hamlet)

- Tent, Lumberjack Camp, Quarry, Farm, Stockpile
- Small House, Well, Guard Tower
- Guild Hall (Basic)

#### Mid Game (Village → Town)

- Sawmill, Mason, Bakery, Warehouse
- Barracks, Walls, Gates
- Weapon Shop, Magic Shop, Tavern, Market

#### Late Game (City)

- Townhouse, Advanced Production Buildings
- Elite Barracks, Training Grounds, Infirmary
- Architect's Office, Alchemist Lab, Strategy Room

---

### 7.2 THREAT PROGRESSION

#### Early Threats (Pop < 30)

- Wolves, Bears
- Bandit Scouts
- **Kingdom Aid Available**

#### Mid Threats (Pop 30-100)

- Goblin Camps
- Bandit Warbands
- Rogue Mages
- **Adventurers Essential**

#### Late Threats (Pop 100+)

- Orc Hordes
- Necromancer Lairs
- Dark Cult Strongholds
- **Advanced Military Needed**

#### End-Game Event

- **"The Scourge" Boss Encounter**
- Requires full city defense, elite adventurers, strategic planning
- Victory = prestige, unique rewards
- Defeat = major losses but city survives

---

## 8. MINIMUM VIABLE PRODUCT (MVP) ROADMAP

### MVP Definition

A playable vertical slice demonstrating core gameplay loop:

- Build a small village
- Gather resources
- Manage villagers
- Hire adventurers
- Face basic threats

---

### PHASE 1: Foundation (Weeks 1-2)

**Goal:** Basic resource gathering and building placement

**Week 1: Core Setup**

- [x] Project setup in UE5 (C++ project)
- [x] Camera controller (WASD movement, zoom, rotate)
- [x] Time control system (pause, 1x, 2x speed)
- [x] Basic terrain (flat plane with simple textures)
- [x] Input handling (left-click select, right-click command)

**Week 2: Resources & Building Basics**

- [ ] Resource data structure (wood, stone, food)
- [ ] Resource node actors (trees, rocks)
- [ ] Villager actor with basic AI (move, idle animations)
- [ ] Resource gathering behavior (villager → tree → chop → carry to stockpile)
- [ ] Building placement system (simple grid or free placement)
- [ ] 3 Buildings: Lumberjack Camp, Quarry, Stockpile

**Milestone 1 Test:** Place buildings, villagers gather wood and stone, resources accumulate in stockpile

---

### PHASE 2: Production & Villagers (Weeks 3-4)

**Week 3: Villager System**

- [ ] Villager needs system (food, water, shelter)
- [ ] Job assignment system (assign villagers to buildings)
- [ ] Housing system (hut building, villager assignment)
- [ ] Well building (water source)
- [ ] Basic UI: resource display (top bar), building menu (bottom)

**Week 4: Processing & Storage**

- [ ] Sawmill building (wood → planks)
- [ ] Production queue system
- [ ] Resource transport (villagers carry from A to B)
- [ ] Warehouse building (storage expansion)
- [ ] Villager AI: work cycle (work → eat → sleep → repeat)

**Milestone 2 Test:** Villagers have homes, gather resources, process them at sawmill, store in warehouse, fulfill needs autonomously

---

### PHASE 3: Guild & Combat Basics (Weeks 5-6)

**Week 5: Guild System**

- [ ] Guild Hall building
- [ ] Adventurer data structure (name, level, class, HP)
- [ ] Adventurer spawning/hiring UI
- [ ] Quest board UI (simple list)
- [ ] Quest creation ("Clear Goblin Camp")
- [ ] Adventurer AI: accept quest → travel to location → execute

**Week 6: Threats & Combat**

- [ ] Threat actor (goblin enemy)
- [ ] Threat spawning system (simple: spawn near city every X minutes)
- [ ] Combat resolution (basic stat comparison)
- [ ] Adventurer combat behavior (auto-attack enemy)
- [ ] Quest completion (enemy defeated → return to guild → reward)
- [ ] Basic soldier system (barracks, guard tower, patrol)

**Milestone 3 Test:** Build guild hall, hire adventurers, send on quest to clear goblin camp, goblins attack city, soldiers defend, adventurers return victorious

---

### PHASE 4: Polish & MVP Complete (Week 7)

**Week 7: Integration & Polish**

- [ ] UI polish (better icons, tooltips, notifications)
- [ ] Visual feedback (resource gathering animations, combat effects)
- [ ] Sound effects (placeholder or free assets)
- [ ] Save/Load system (basic)
- [ ] Threat escalation (ignored threats spawn more enemies)
- [ ] Balance pass (resource costs, production rates, combat difficulty)

**Milestone 4: MVP COMPLETE**

- Player can build a small village
- Villagers autonomously gather, process, and fulfill needs
- Guild system allows hiring adventurers and clearing threats
- Basic threat system attacks city periodically
- Soldiers provide basic defense

---

## 9. MISSING PIECES & OPEN QUESTIONS

### Design Decisions Needed

#### 1. Research/Unlocking System

**Question:** How do players unlock new buildings?

- **Option A:** Research tree (Architect Office building)
- **Option B:** Population milestones (automatic)
- **Option C:** Hybrid (most auto, some researched)

**My Recommendation:** Start with **Option B (Milestones)** for MVP, add research tree post-MVP if needed.

---

#### 2. Adventurer Rank/Level System

**Question:** S/A/B/C rank or numerical levels (1-20)?

- **Rank (S/A/B/C):** Simpler, easier to understand at a glance
- **Level (1-20):** More granular progression, familiar to players

**My Recommendation:** Use **numerical levels (1-20)** for clarity and easier balancing. Optionally, display rank as a derived stat (Level 1-5 = C, 6-10 = B, etc.)

---

#### 3. Scout System

**Question:** Are scouts separate from adventurers, or a class?

- **Option A:** Separate unit type (hired from different building)
- **Option B:** Adventurer class (some adventurers are scouts)
- **Option C:** Any adventurer can scout (scout quest type)

**My Recommendation:** **Option C** for simplicity. Any adventurer can take a "Scout" quest, which reveals threat info.

---

#### 4. Shop Pricing & Economy Balance

**Question:** How are shop prices determined?

- **Option A:** Player sets prices (micromanagement)
- **Option B:** Auto-balanced by game (simpler)
- **Option C:** Dynamic pricing (complex)

**My Recommendation:** **Option B** for MVP. Auto-price items based on resource costs. Add player pricing controls post-MVP if desired.

---

#### 5. Road Formation System

**Question:** How do roads form organically?

- **Technical Challenge:** Track villager paths, generate road meshes dynamically
- **Alternative:** Pre-defined road placement (simpler)

**My Recommendation:** **Pre-defined road placement for MVP**. Add organic road formation as a **post-MVP feature** (requires complex pathfinding data tracking).

---

#### 6. End-Game Content

**Question:** What happens after "The Scourge" is defeated?

- **Option A:** Sandbox continues indefinitely
- **Option B:** New threats spawn, escalating difficulty
- **Option C:** New Game+ mode unlocks

**My Recommendation:** **Option A** for MVP. Post-victory, threats continue at manageable levels. Add NG+ or endless mode post-MVP.

---

#### 7. Adventurer Permadeath Severity

**Question:** Is permadeath too punishing?

- **Risk:** Players may find losing high-level adventurers frustrating
- **Mitigation:** Resurrection mechanic? Gear recovery?

**My Recommendation:** Keep permadeath BUT add **Infirmary resurrection** (expensive, limited uses) as a mid-game unlock. This maintains stakes while reducing frustration.

---

### Content Gaps to Fill Later

#### Art & Animation

- Villager models & animations (idle, walk, work)
- Adventurer models (4 classes, male/female variations)
- Enemy models (wolves, goblins, orcs, necromancers)
- Building models (20+ unique buildings)
- Environment assets (trees, rocks, grass, roads)

**MVP Approach:** Use **free/purchased asset packs** or **placeholder cubes** initially.

#### Audio

- Background music (peaceful city ambiance, combat tension)
- Sound effects (hammering, chopping, combat, UI clicks)

**MVP Approach:** Use **free sound libraries** (Freesound.org, ZapSplat).

#### Narrative/Events

- Random events (caravan arrival, festival, plague, etc.)
- Quest flavor text (make quests feel unique)
- Lore about "The Scourge" and world

**MVP Approach:** Minimal text, focus on gameplay. Add flavor post-MVP.

---

## 10. RISK ASSESSMENT

### High Risks

#### Risk 1: Scope Creep

**Description:** Feature list expands beyond MVP, project never finishes.
**Mitigation:** 

- Strict adherence to MVP roadmap
- "Post-MVP" list for all new ideas
- Weekly scope review

#### Risk 2: Performance Issues (AI/Pathfinding)

**Description:** Too many villagers/adventurers tank FPS.
**Mitigation:**

- Early performance testing (spawn 200 villagers)
- AI throttling (update every 0.5s)
- Pathfinding optimizations (hierarchical, caching)

#### Risk 3: Motivation Loss

**Description:** Project feels overwhelming, progress stalls.
**Mitigation:**

- **30-day challenge structure** (see below)
- Daily small wins
- Community accountability (DevLog, Discord)
- Playtest milestones

### Medium Risks

#### Risk 4: Combat Balance

**Description:** Combat feels too random or unfair.
**Mitigation:**

- Transparent stat displays
- Clear difficulty ratings
- Extensive playtesting

#### Risk 5: UI Complexity

**Description:** Too much info overwhelms player.
**Mitigation:**

- Iterative UI design
- Tooltips and tutorials
- Hide advanced info behind toggles

---

## POST-MVP FEATURE BACKLOG

### Phase 2 (Post-MVP) Features

- Organic road formation system
- Research/tech tree
- Advanced military units (battle mages, knights)
- More threat types (undead, demons, dragons)
- Seasonal weather system
- Trade caravans & diplomacy with other settlements
- Villager traits & relationships
- Advanced needs (religion, entertainment tiers)
- Quest procedural generation
- Modding support

### Phase 3 (Polish & Expansion)

- Campaign mode with story
- Multiple biomes (desert, snow, swamp)
- Multiplayer co-op (shared city)
- Steam Workshop integration
- Full voice acting & orchestral soundtrack

---

## APPENDIX

### Inspirations & References

- **Foundation** - Organic city building, relaxed pace
- **Banished** - Resource survival, villager autonomy
- **Anno Series** - Production chains, supply management
- **They Are Billions** - Tower defense, threat escalation
- **RimWorld** - Agent-based simulation (but lighter)
- **Dwarf Fortress (Steam)** - Indirect control, emergent gameplay

### Tools & Resources

- **Unreal Engine 5** - Game engine
- **Rider or Visual Studio** - C++ IDE
- **Blender** - 3D asset creation (if needed)
- **Mixamo** - Free character animations
- **Quixel Megascans** - Environment assets
- **GitHub** - Version control

---

**END OF GDD v1.0**
