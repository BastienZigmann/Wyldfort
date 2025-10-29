// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/AnimInstances/VillagerAnimInstance.h"
#include "Characters/Villager.h"

UVillagerAnimInstance::UVillagerAnimInstance()
{
    Speed = 0;
    CachedOwningVillager = nullptr;
}

void UVillagerAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    TryGetSetOwningVillager();
}

void UVillagerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    AVillager* Villager = TryGetSetOwningVillager();
    if (Villager)
    {
        FVector velocity = Villager->GetVelocity();
        Speed = FVector(velocity.X, velocity.Y, 0.0f).Size();

    }
}

AVillager* UVillagerAnimInstance::TryGetSetOwningVillager()
{
    if (!CachedOwningVillager)
        CachedOwningVillager = Cast<AVillager>(GetOwningActor());
    return CachedOwningVillager;
}