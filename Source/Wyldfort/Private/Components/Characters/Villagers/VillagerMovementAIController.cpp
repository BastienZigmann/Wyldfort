// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Characters/Villagers/MovementAIController.h"
#include "Components/Characters/Villagers/VillagerMovementComponent.h"
#include "Characters/Villager.h"
#include "Navigation/PathFollowingComponent.h"


void AMovementAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    Super::OnMoveCompleted(RequestID, Result);

    AVillager* Villager = Cast<AVillager>(GetPawn());
    if (!Villager) return;    

    if (UVillagerMovementComponent* VillagerMovementComponent = Villager->GetVillagerMovementComponent())
    {
        VillagerMovementComponent->OnMoveCompleted(Result.IsSuccess());
    }
}