// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Global/ResourceComponent.h"

UResourceComponent::UResourceComponent() 
{
    PrimaryComponentTick.bCanEverTick = false;
}

FResourceStack UResourceComponent::Gather() 
{
    if (IsDepleted()) return FResourceStack{};
    
    int32 gathered = FMath::Min(TotalAmount, AmountPerGather);

    FResourceStack stack;
    stack.Type = Type;
    stack.Quantity = gathered;

    TotalAmount -= gathered;
    if (TotalAmount == 0)
    {
        bDepleted = true;
        OnDepleted.Broadcast();
    }

    return stack;
}