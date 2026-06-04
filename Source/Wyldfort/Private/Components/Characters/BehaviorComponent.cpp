// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Characters/BehaviorComponent.h"
#include "AI/States/BaseBehaviorState.h"

UBehaviorComponent::UBehaviorComponent()
{
    CurrentState = nullptr; // init with IDLE
}

void UBehaviorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    if (CurrentState) CurrentState->Update(DeltaTime);
}

void UBehaviorComponent::SetState(UBaseBehaviorState newState)
{
    //if (CurrentState) CurrentState.Exit();
}