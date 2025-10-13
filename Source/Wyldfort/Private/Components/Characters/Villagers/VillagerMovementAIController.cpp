// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Characters/Villagers/MovementAIController.h"
#include "Characters/Villager.h"
#include "Navigation/PathFollowingComponent.h"


void AMovementAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    Super::OnMoveCompleted(RequestID, Result);

    UE_LOG(LogTemp, Log, TEXT("MovementAIController: OnMoveCompleted called with RequestID: %s, Result: %s"), *RequestID.ToString(), *Result.ToString());

    if (AVillager* Villager = Cast<AVillager>(GetPawn()))
    {
        if (Result.IsSuccess())
            Villager->OnMoveCompleted();
        else
            Villager->OnMoveFailed();
    }
}