# Wyldfort — Architecture & File Structure

> **Maintenance rule:** This file must be updated every time a file is added, moved, renamed or deleted.
> Each entry covers both the `.h` and `.cpp` pair — no need to list them separately.

---

## Structural Rules

| Rule | Description |
|---|---|
| `Core/Bases/` | Pure UE-type wrappers only (`AActor`, `ACharacter`, `UActorComponent`, `UWorldSubsystem`, `UUserWidget`). Zero game-domain knowledge. Extractable to any UE project. |
| `Core/Utils/` | Stateless utility mixins and helpers with no game knowledge. |
| Domain base classes | Live **alongside their children**, not in `Core/`. Example: `BaseBuilding` lives in `Buildings/`. |
| Types / Enums | Live **next to the domain they describe**. Example: `BuildingTypes` lives in `Buildings/`. |
| `AI/Controllers/` | AIController subclasses only. Not components. |
| `AI/States/` | Behavior state objects. Subfolders per character type. |
| `Components/Characters/` | Generic character components (applicable to villagers, guards, adventurers...). |
| `Components/Characters/Villagers/` | Components specific to villagers only. |
| `Components/Global/` | Components usable by any actor regardless of type. |

---

## File Tree

```
Source/Wyldfort/
├── Public / Private (mirrored)
│
├── WyldfortGameMode
│     Game mode entry point, minimal setup
│
├── CameraPawn
│     Top-down RTS camera pawn, handles zoom and pan
│
├── CameraPlayerController
│     Player controller bound to CameraPawn, handles input
│
├── AI/
│   ├── Controllers/
│   │   └── MovementAIController
│   │         AAIController subclass. Bridges UE pathfinding OnMoveCompleted
│   │         to VillagerMovementComponent
│   │
│   └── States/
│       ├── BaseBehaviorState
│       │     Abstract base for all behavior states. Holds owner ref,
│       │     Enter/Update/Exit interface, GetOwner<T>() template, ESubState enum
│       │     (NONE, GOTO, DO, GO_BACK)
│       │
│       └── Villager/
│           └── VillagerIdleState
│                 Initial villager state on spawn. Stub — will transition
│                 to first active state (eat or work)
│
├── Animations/
│   └── AnimInstances/
│       └── VillagerAnimInstance
│             UAnimInstance subclass driving villager animations
│             (movement speed, state transitions)
│
├── Buildings/
│   ├── BaseBuilding
│   │     Domain base for all buildings. Manages entry/exit/pause points,
│   │     self-registers to VillageBuildingsManagerSubsystem,
│   │     exposes GetEntryPointTransform / GetExitPointTransform
│   │
│   ├── BaseGatheringBuilding
│   │     Extends BaseBuilding. Manages resource scanning, worker assignment,
│   │     ResourceNode spawning, depletion handling and inventory handoff
│   │
│   ├── BuildingTypes
│   │     EBuildingType enum (House, FoodMarket, Well, WoodCuttingCamp...)
│   │     EBuildingInteractionType enum (Enter, Gather, Wait...)
│   │
│   ├── FoodMarket        — Villagers eat here
│   ├── House             — Villagers sleep here
│   ├── Well              — Villagers drink here
│   ├── SawMill           — [WIP]
│   ├── WoodCuttingCamp
│   │     Concrete gathering building. Scans for gatherable trees,
│   │     assigns villager workers to ResourceNodes
│   │
│   └── Parts/
│       ├── EntryPoint    — Child actor. Navigation target for entering a building
│       ├── ExitPoint     — Child actor. Navigation target for leaving a building.
│       │                   Best exit chosen by dot product toward next destination
│       └── PausePoint    — Child actor. Navigation target for buildings that do not
│                           require full entry (e.g. Well)
│
├── Characters/
│   ├── BaseCharacter
│   │     Domain base for all characters. Extends ACharacter + FLogger.
│   │     Holds UInventoryComponent. Used by villagers, guards, adventurers, merchants
│   │
│   └── Villager
│         Concrete villager character. Holds raw hunger/thirst/fatigue floats
│         (to be moved to NeedsComponent later). Owns VillagerMovementComponent,
│         TimeAffectedComponent, BehaviorComponent.
│         Assigned a work building via SetWorkBuilding()
│
├── Components/
│   ├── Characters/
│   │   ├── BehaviorComponent
│   │   │     Generic character behavior state machine. Holds CurrentState,
│   │   │     drives Update(DeltaTime) each tick. SetState<T>() exits current
│   │   │     state, creates and enters new one.
│   │   │     Used by any character type (villager, guard, adventurer...)
│   │   │
│   │   └── Villagers/
│   │       ├── BaseVillagerComponent
│   │       │     Base for all villager-specific components.
│   │       │     Extends UBaseActorComponent. Provides GetOwningVillager() accessor
│   │       │
│   │       └── VillagerMovementComponent
│   │             Manages villager navigation. Holds CurrentDestination,
│   │             calls AIController MoveToLocation, broadcasts OnDestinationReached
│   │             delegate on arrival. PickNextDestination() is legacy — to be
│   │             removed once state system drives destinations
│   │
│   └── Global/
│       ├── InventoryComponent
│       │     Generic inventory. Holds TArray of FResourceStack.
│       │     Used by villagers and gathering buildings
│       │
│       └── TimeAffectedComponent
│             Registers owner to TimeControlSubsystem so game speed dilation
│             applies to this actor's timers and tick
│
├── Core/
│   ├── Bases/
│   │   ├── BaseActor
│   │   │     AActor + FLogger. Root base for all non-character actors
│   │   │
│   │   ├── BaseSubsystem
│   │   │     UWorldSubsystem + FLogger. Root base for all subsystems
│   │   │
│   │   ├── BaseUserWidget
│   │   │     UUserWidget + FLogger. Root base for all UI widgets
│   │   │
│   │   └── Components/
│   │       └── BaseActorComponent
│   │             UActorComponent + FLogger + GetOwnerTyped<T>() +
│   │             GetOwnerComponent<T>() helpers. Root base for all components
│   │
│   └── Utils/
│       └── Logger
│             FLogger mixin. Provides DebugLog() / WarningLog() / ErrorLog()
│             with owner context. Mixed into all Base classes
│
├── Interface/
│   ├── MainHUDWidget             — Main in-game HUD overlay
│   └── GameSpeedControlWidget    — UI for game speed control (pause / x1 / x2 / x3)
│
├── Resources/
│   ├── ResourceTypes
│   │     EResourceType enum (Wood, Stone, Food...) and FResourceStack struct
│   │
│   ├── GatherableFoliage
│   │     Actor representing a gatherable foliage instance.
│   │     Manages ISM index and depletion state
│   │
│   └── ResourceNode
│         Actor spawned at a foliage location when a villager is assigned.
│         Holds gather rate, remaining quantity, fires OnDepleted delegate
│
└── Subsystems/
    ├── VillageBuildingsManagerSubsystem
    │     World subsystem. Maintains TMap of EBuildingType to TArray of buildings.
    │     Buildings self-register on BeginPlay.
    │     Exposes GetClosestBuildingByType(Type, Location)
    │
    └── TimeControlSubsystem
          World subsystem. Manages global game speed and time dilation.
          Notifies registered TimeAffectedComponents on change
```

---

## Inheritance Overview

```
AActor
└── ABaseActor : FLogger
    └── ABaseBuilding
        ├── ABaseGatheringBuilding
        │   └── AWoodCuttingCamp
        ├── AFoodMarket
        ├── AHouse
        ├── AWell
        ├── ASawMill
        └── [Parts] AEntryPoint, AExitPoint, APausePoint
    └── AGatherableFoliage
    └── AResourceNode

ACharacter
└── ABaseCharacter : FLogger
    └── AVillager

AAIController
└── AMovementAIController

UActorComponent
└── UBaseActorComponent : FLogger
    └── UBaseVillagerComponent
        └── UVillagerMovementComponent
    └── UBehaviorComponent
    └── UInventoryComponent
    └── UTimeAffectedComponent

UWorldSubsystem
└── UBaseSubsystem : FLogger
    ├── UVillageBuildingsManagerSubsystem
    └── UTimeControlSubsystem

UUserWidget
└── UBaseUserWidget : FLogger
    ├── UMainHUDWidget
    └── UGameSpeedControlWidget

UObject
└── UBaseBehaviorState
    └── UVillagerIdleState

APawn
└── ACameraPawn

APlayerController
└── ACameraPlayerController

UAnimInstance
└── UVillagerAnimInstance
```

---

## Upcoming (not yet created)

| File | Location | Purpose |
|---|---|---|
| `VillagerWorkState` | `AI/States/Villager/` | GOTO work building, DO gather loop, GO_BACK drop inventory |
| `VillagerEatState` | `AI/States/Villager/` | GOTO FoodMarket, DO eat (timer), transition to next state |
| `VillagerDrinkState` | `AI/States/Villager/` | GOTO Well, DO drink (timer), transition to next state |
| `VillagerSleepState` | `AI/States/Villager/` | GOTO House, DO sleep (timer), transition to next state |
| `NeedsComponent` | `Components/Characters/` | Hunger / Thirst / Energy floats with passive decay. Replaces raw fields on AVillager |
