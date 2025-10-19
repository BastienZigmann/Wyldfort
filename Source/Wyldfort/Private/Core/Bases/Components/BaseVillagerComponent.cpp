// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Bases/Components/BaseVillagerComponent.h"

UBaseVillagerComponent::UBaseVillagerComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;

    // ...
}

void UBaseVillagerComponent::BeginPlay()
{
    Super::BeginPlay();

    OwningVillager = GetOwnerTyped<AVillager>();
    if (!OwningVillager)
    {
        ErrorLog(TEXT("Owning villager is null!"), this);
        return;
    }
}

AVillager* UBaseVillagerComponent::GetOwningVillager()
{
    return OwningVillager;
}
