// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Characters/Villagers/VillagerMovementComponent.h"
#include "Subsystems/VillageBuildingsManagerSubsystem.h"
#include "Engine/World.h"
#include "NavigationSystem.h"
#include <AIController.h>
#include "Core/Bases/BaseBuilding.h"

UVillagerMovementComponent::UVillagerMovementComponent()
{
    tmp = 0;

    PrimaryComponentTick.bCanEverTick = false;
    CurrentDestination = nullptr;
    EnableDebug();
}

void UVillagerMovementComponent::BeginPlay()
{
    Super::BeginPlay();
    DebugLog("Villager Movement component Initialized", this);
}

void UVillagerMovementComponent::PickNextDestination()
{
    DebugLog("Picking next destination...", this);
    // Placeholder for destination picking logic
    if (UWorld* World = GetWorld())
    {
        if (UVillageBuildingsManagerSubsystem* Subsys = World->GetSubsystem<UVillageBuildingsManagerSubsystem>())
        {
            ABaseBuilding* Destination = Subsys->GetClosestBuildingByType(EBuildingType::House, GetOwningVillager()->GetActorLocation());
            if (tmp % 2 == 0) Destination = Subsys->GetClosestBuildingByType(EBuildingType::FoodMarket, GetOwningVillager()->GetActorLocation());;
            tmp ++;

            if (Destination)
            {
                CurrentDestination = Destination;
                DebugLog("New destination acquired.", this);
            }
        }
    }
}

void UVillagerMovementComponent::MoveToDestination()
{
    if (!CurrentDestination) return;

    if (AAIController* AICon = Cast<AAIController>(GetOwningVillager()->GetController()))
    {
        FVector Goal = CurrentDestination->GetDestinationTransform(GetOwningVillager()->GetActorLocation()).GetLocation();
        if (const UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld()))
        {
            FNavLocation NavLoc;
            if (NavSys->ProjectPointToNavigation(Goal, NavLoc))
                Goal = NavLoc.Location;
        }
        DebugLog("Moving to destination", this);

        AICon->MoveToLocation(Goal, -1, /*bStopOnOverlap*/true, /*bUsePathfinding*/true,
                              /*bProjectDestinationToNavigation*/false, /*bCanStrafe*/false, /*Filter*/nullptr);
    }
}

void UVillagerMovementComponent::OnMoveCompleted(bool bSuccess)
{
    if (bSuccess)
        DebugLog("Successfully arrived at destination.", this);
    else
        WarningLog("Failed to reach destination.", this);
    OnDestinationReached.Broadcast();
    PickNextDestination();
    MoveToDestination();
}
