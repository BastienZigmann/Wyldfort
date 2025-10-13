// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Villager.h"
#include "Subsystems/VillageManagerSubsystem.h"
#include "Engine/World.h"
#include <AIController.h>
#include "NavigationSystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Core/Bases/BaseBuilding.h"
#include "Components/Characters/Villagers/MovementAIController.h"

AVillager::AVillager()
{
    PrimaryActorTick.bCanEverTick = true;

    AIControllerClass = AMovementAIController::StaticClass();

    Hunger = 100.0f;
    Thirst = 100.0f;
    Fatigue = 100.0f;

    CurrentDestination = nullptr;

    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    GetCharacterMovement()->bOrientRotationToMovement = true; 
    
    EnableDebug();
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
    PickNextDestination();
    MoveToDestination();
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

void AVillager::PickNextDestination()
{
    // Placeholder for destination picking logic
    if (UWorld* World = GetWorld())
    {
        if (UVillageManagerSubsystem* Subsys = World->GetSubsystem<UVillageManagerSubsystem>())
        {
            ABaseBuilding* Destination = Subsys->GetClosestBuildingByType(EBuildingType::House, GetActorLocation());
            if (Destination)
            {
                CurrentDestination = Destination;
                DebugLog("New destination acquired.", this);
            }
        }
    }
}

void AVillager::MoveToDestination()
{
    if (!CurrentDestination) return;

    if (AAIController* AICon = Cast<AAIController>(GetController()))
    {
        // Optional: project target to navmesh
        FVector Goal = CurrentDestination->GetDestinationTransform(GetActorLocation()).GetLocation();
        if (const UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld()))
        {
            FNavLocation NavLoc;
            if (NavSys->ProjectPointToNavigation(Goal, NavLoc))
            {
                Goal = NavLoc.Location;
            }
        }
        DebugLog("Moving to destination", this);

        AICon->MoveToLocation(Goal, -1, /*bStopOnOverlap*/true, /*bUsePathfinding*/true,
                              /*bProjectDestinationToNavigation*/false, /*bCanStrafe*/false, /*Filter*/nullptr);
    }
}

void AVillager::OnMoveCompleted()
{
    DebugLog("Arrived at destination.", this);
    // if (Result.IsSuccess())
    // {
    //     DebugLog("Arrived at destination.", this);
    //     // Simulate interaction time
    //     GetWorldTimerManager().SetTimerForNextTick(this, &AVillager::PickNextDestination);
    //     GetWorldTimerManager().SetTimerForNextTick(this, &AVillager::MoveToDestination);
    // }
    // else
    // {
    //     DebugLog("Failed to reach destination.", this);
    //     // Retry or pick a new destination
    //     PickNextDestination();
    //     MoveToDestination();
    // }
}

void AVillager::OnMoveFailed()
{
    DebugLog("Failed to reach destination.", this);
}

