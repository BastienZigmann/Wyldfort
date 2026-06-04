// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Characters/BehaviorComponent.h"
#include "Components/Characters/NeedsComponent.h"
#include "Characters/BaseCharacter.h"
#include "AI/States/BaseBehaviorState.h"
#include "AI/States/Villager/VillagerIdleState.h"
#include "AI/States/StatesTransitionInfo.h"

UBehaviorComponent::UBehaviorComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    EnableDebug(true);
    
    CurrentState = nullptr; // init with IDLE

}

void UBehaviorComponent::BeginPlay() 
{
    Super::BeginPlay();
    ABaseCharacter* owningCharacter = GetOwnerTyped<ABaseCharacter>();
    if (!owningCharacter)
    {
        ErrorLog("Failed to get Owning Character", this);
        return;
    }
    owningCharacter->GetNeedsComponent()->OnHungerCritical.AddUObject(this, &UBehaviorComponent::OnCriticalStarving);
    owningCharacter->GetNeedsComponent()->OnThirstCritical.AddUObject(this, &UBehaviorComponent::OnCriticalThirsty);

}

void UBehaviorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if (!CurrentState) return;
    CurrentState->Update(DeltaTime);
    UBaseBehaviorState* NewState = CurrentState->GetNextState();
    SetNewState(NewState);
}

void UBehaviorComponent::OnCriticalStarving() 
{
    DebugLog("Hunger Critical", this);
    FStatesTransitionInfo transitionInfo;
    transitionInfo.isCriticalHungry = true;
    
    ComputeTransition(transitionInfo);
}

void UBehaviorComponent::OnCriticalThirsty()
{
    DebugLog("ThirstCritical", this);
    FStatesTransitionInfo transitionInfo;
    transitionInfo.isCriticalThrist = true;

    ComputeTransition(transitionInfo);
}

void UBehaviorComponent::SetNewState(UBaseBehaviorState* NewState)
{
    if (!NewState) return;
    DebugLog("New State: ", this);
    CurrentState->Exit();
    CurrentState->MarkAsGarbage();
    NewState->Init(GetOwnerTyped<ABaseCharacter>());
    CurrentState = MoveTemp(NewState);
    NewState->Enter();
}

void UBehaviorComponent::ComputeTransition(const FStatesTransitionInfo& transitionInfo)
{
    UBaseBehaviorState* NewState = CurrentState->HandleTransition(transitionInfo);
    SetNewState(NewState);    
}