// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/VillagerManagerSubsystem.h"
#include "Characters/Villager.h"

UVillagerManagerSubsystem::UVillagerManagerSubsystem()
{
    EnableDebug();
}

void UVillagerManagerSubsystem::RegisterVillager(AVillager* Villager)
{
    if (!Villager) return;

    RegisteredVillager.Add(Villager);
    DebugLog("Villager Registered", this);
}

void UVillagerManagerSubsystem::UnregisterVillager(AVillager* Villager)
{
    if (!Villager) return;

    RegisteredVillager.Remove(Villager);
    DebugLog("Villager Unregistered", this);
}

TArray<AVillager*> UVillagerManagerSubsystem::GetUnemployedVillagers()
{
    TArray<AVillager*> res;
    for (TWeakObjectPtr<AVillager> v : RegisteredVillager)
        if(v != nullptr && !v->HasWork())
            res.Add(v.Get());
    return res;
}