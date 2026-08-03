// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Villager.h"
#include "AI/Controllers/MovementAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/Characters/Villagers/VillagerMovementComponent.h"
#include "Subsystems/VillagerManagerSubsystem.h"

AVillager::AVillager()
{
    // EnableDebug();
    PrimaryActorTick.bCanEverTick = false;

    AIControllerClass = AMovementAIController::StaticClass();

    VillagerMovementComponent = CreateDefaultSubobject<UVillagerMovementComponent>(TEXT("VillagerMovementComponent"));
    if (!VillagerMovementComponent) 
    {
        ErrorLog("Failed to create VillagerMovementComponent!", this);
        return;
    }

    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    GetCharacterMovement()->bOrientRotationToMovement = true; 
    DebugLog("Village initialized", this);
}

void AVillager::BeginPlay()
{
    Super::BeginPlay();
    
    if (UWorld* World = GetWorld())
    {
        if (UVillagerManagerSubsystem* Subsys = World->GetSubsystem<UVillagerManagerSubsystem>())
        {
            Subsys->RegisterVillager(this);
        }
    }

    DebugLog("Villager spawned.", this);
}

void AVillager::EndPlay(const EEndPlayReason::Type Reason)
{
    Super::EndPlay(Reason);

    if (UWorld* World = GetWorld())
    {
        if (UVillagerManagerSubsystem* Subsys = World->GetSubsystem<UVillagerManagerSubsystem>())
        {
            Subsys->UnregisterVillager(this);
        }
    }

    DebugLog("Villager despawned.", this);
}

void AVillager::SetWorkBuilding(ABaseBuilding* Building) 
{ 
    Work = Building; 
}