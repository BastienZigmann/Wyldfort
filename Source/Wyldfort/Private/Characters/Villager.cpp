// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Villager.h"
#include "Subsystems/VillageManagerSubsystem.h"
#include "Engine/World.h"
#include <AIController.h>
#include "NavigationSystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Buildings/BaseBuilding.h"

AVillager::AVillager()
{
    PrimaryActorTick.bCanEverTick = true;

    Hunger = 100.0f;
    Thirst = 100.0f;
    Fatigue = 100.0f;

    CurrentDestination = nullptr;

    AIControllerClass = AAIController::StaticClass(); // or your custom AVillagerAIController
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
        FVector Goal = CurrentDestination->GetActorLocation();
        if (const UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld()))
        {
            FNavLocation NavLoc;
            if (NavSys->ProjectPointToNavigation(Goal, NavLoc, FVector(200,200,400)))
            {
                Goal = NavLoc.Location;
            }
        }

        AICon->MoveToLocation(Goal, -1, /*bStopOnOverlap*/true, /*bUsePathfinding*/true,
                              /*bProjectDestinationToNavigation*/false, /*bCanStrafe*/false, /*Filter*/nullptr);
    }
}
