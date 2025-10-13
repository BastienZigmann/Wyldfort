// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/VillageManagerSubsystem.h"
#include "Core/Bases/BaseBuilding.h"
#include "Core/Types/BuildingTypes.h"

UVillageManagerSubsystem::UVillageManagerSubsystem()
{
    EnableDebug();
}

void UVillageManagerSubsystem::RegisterBuilding(ABaseBuilding* Building)
{
    if (!Building) return;

    EBuildingType Type = Building->GetBuildingType();
    if (Type == EBuildingType::None)
    {
        WarningLog("Attempted to register building with type 'None'.", this);
        return;
    }

    RegisteredBuildings.FindOrAdd(Type).Add(Building);
    DebugLog(FString::Printf(TEXT("Registered building of type %d."), static_cast<uint8>(Type)), this);
}

void UVillageManagerSubsystem::UnregisterBuilding(ABaseBuilding* Building)
{
    if (!Building) return;

    EBuildingType Type = Building->GetBuildingType();
    if (Type == EBuildingType::None)
    {
        WarningLog("Attempted to unregister building with type 'None'.", this);
        return;
    }

    if (TArray<TWeakObjectPtr<ABaseBuilding>>* Buildings = RegisteredBuildings.Find(Type))
    {
        Buildings->Remove(Building);
        DebugLog(FString::Printf(TEXT("Unregistered building of type %d."), static_cast<uint8>(Type)), this);
    }
}

ABaseBuilding* UVillageManagerSubsystem::GetClosestBuildingByType(EBuildingType Type, const FVector& Location) const
{
    if (Type == EBuildingType::None) return nullptr;

    DebugLog(FString::Printf(TEXT("Searching for closest building of type %d."), static_cast<uint8>(Type)), this);

    ABaseBuilding* ClosestBuilding = nullptr;
    if (const TArray<TWeakObjectPtr<ABaseBuilding>>* Buildings = RegisteredBuildings.Find(Type))
    {
        float ClosestDistanceSquared = TNumericLimits<float>::Max();
        for (const TWeakObjectPtr<ABaseBuilding>& BuildingPtr : *Buildings)
        {
            if (BuildingPtr.IsValid())
            {
                float DistanceSquared = FVector::DistSquared(BuildingPtr->GetActorLocation(), Location);
                if (DistanceSquared < ClosestDistanceSquared)
                {
                    ClosestDistanceSquared = DistanceSquared;
                    ClosestBuilding = BuildingPtr.Get();
                    DebugLog(FString::Printf(TEXT("New closest building found")), this);
                }
            }
        }
    }
    return ClosestBuilding;
}