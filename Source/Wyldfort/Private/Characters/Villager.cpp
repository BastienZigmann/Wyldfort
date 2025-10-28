// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Villager.h"
#include "Components/Characters/Villagers/MovementAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/Characters/Villagers/VillagerMovementComponent.h"
#include "Components/Global/TimeAffectedComponent.h"

AVillager::AVillager()
{
    EnableDebug();
    PrimaryActorTick.bCanEverTick = true;

    AIControllerClass = AMovementAIController::StaticClass();

    Hunger = 100.0f;
    Thirst = 100.0f;
    Fatigue = 100.0f;

    TimeAffectedComponent = CreateDefaultSubobject<UTimeAffectedComponent>(TEXT("TimeAffectedComponent"));
    VillagerMovementComponent = CreateDefaultSubobject<UVillagerMovementComponent>(TEXT("VillagerMovementComponent"));
    if (!VillagerMovementComponent) 
    {
        DebugLog("Failed to create VillagerMovementComponent!", this);
        return;
    }

    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    GetCharacterMovement()->bOrientRotationToMovement = true; 
    DebugLog("Village initialized", this);
}

void AVillager::BeginPlay()
{
    Super::BeginPlay();
    
    DebugLog("Villager spawned.", this);
    GetWorldTimerManager().SetTimerForNextTick(this, &AVillager::StartInitialMove);
}

void AVillager::StartInitialMove()
{
    DebugLog("Villager starting initial move.", this);
    VillagerMovementComponent->PickNextDestination();
    VillagerMovementComponent->MoveToDestination();
}


void AVillager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    Hunger -= DeltaTime * 0.1f;
    Thirst -= DeltaTime * 0.2f;
    Fatigue -= DeltaTime * 0.05f;

    if (Hunger <= 0.0f || Thirst <= 0.0f || Fatigue <= 0.0f)
    {
        DebugLog("Villager is in critical condition!", this);
    }
}
