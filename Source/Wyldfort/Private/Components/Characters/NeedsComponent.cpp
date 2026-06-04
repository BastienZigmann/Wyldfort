// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Characters/NeedsComponent.h"

UNeedsComponent::UNeedsComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    EnableDebug(false);
    DebugLog("NeedsComponent created", this);
}

void UNeedsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    Hunger = FMath::Max(0, Hunger - DecayRate * DeltaTime); // Update
    if (OnHungerChanged.IsBound()) // Notify for UI
        OnHungerChanged.Broadcast(Hunger);
    if (!bHungerCriticalFired && Hunger <= CriticalThreshold && OnHungerCritical.IsBound()) // Notify for behavior
    {
        DebugLog("Starving", this);
        bHungerCriticalFired = true;
        OnHungerCritical.Broadcast();
    }
    
    Thirst = FMath::Max(0, Thirst - DecayRate * DeltaTime); // Update
    if (OnThirstChanged.IsBound()) // Notify for UI
        OnThirstChanged.Broadcast(Thirst);
    if (!bThirstCriticalFired && Thirst <= CriticalThreshold && OnThirstCritical.IsBound()) // Notify for behavior
    {
        DebugLog("In critical need of water", this);
        bThirstCriticalFired = true;
        OnThirstCritical.Broadcast();
    }
}

void UNeedsComponent::Feed(const float Amount)
{
    Hunger = Amount == 0 ? 100 : Amount;
    if (Hunger > CriticalThreshold) // If fed enough, reset notification flag
        bHungerCriticalFired = false;
    DebugLog("Fed", this);
}

void UNeedsComponent::Drink(const float Amount)
{
    Thirst = Amount == 0 ? 100 : Amount;
    if (Thirst > CriticalThreshold) // If fed enough, reset notification flag
        bThirstCriticalFired = false;
    DebugLog("Drank", this);
}