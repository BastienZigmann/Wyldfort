// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Characters/BehaviorComponent.h"
#include "Components/Characters/NeedsComponent.h"
#include "Characters/BaseCharacter.h"
#include "AI/States/BaseBehaviorState.h"

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
    if (CurrentState) CurrentState->Update(DeltaTime);
}

void UBehaviorComponent::OnCriticalStarving() 
{
    DebugLog("Hunger Critical", this);
}

void UBehaviorComponent::OnCriticalThirsty()
{
    DebugLog("ThirstCritical", this);
}