// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Bases/BaseSubsystem.h"
#include "Core/Types/BuildingTypes.h"
#include "VillageBuildingsManagerSubsystem.generated.h"

class ABaseBuilding;
class AHouse;
class FoodMarket;
class AWell;

UCLASS()
class WYLDFORT_API UVillageBuildingsManagerSubsystem : public UBaseSubsystem
{
	GENERATED_BODY()
	
public:
	UVillageBuildingsManagerSubsystem();
	// virtual void Initialize(FSubsystemCollectionBase& Collection) override; // Override only if you have setup work when the subsystem is created for a world (e.g., caching subsystems, binding delegates, creating timers).
    // virtual void Deinitialize() override; // Override if you need to unbind delegates, clear timers, release resources. Otherwise you can omit it.
    // virtual void OnWorldBeginPlay(UWorld& InWorld) override; // Override if you need logic specifically when the world starts playing (after the world is ready). If not, omit it.

	void RegisterBuilding(class ABaseBuilding* Building);
	void UnregisterBuilding(class ABaseBuilding* Building);

	ABaseBuilding* GetClosestBuildingByType(EBuildingType Type, const FVector& Location) const;


private:
	TMap<EBuildingType, TArray<TWeakObjectPtr<ABaseBuilding>>> RegisteredBuildings;

};
