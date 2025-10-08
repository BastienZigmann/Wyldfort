// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Bases/BaseActor.h"
#include "Core/Types/BuildingTypes.h"
#include "BaseBuilding.generated.h"

class UArrowComponent;
class UBoxComponent;
class AEntryPoint;
class AExitPoint;
class APausePoint;

UCLASS()
class WYLDFORT_API ABaseBuilding : public ABaseActor
{
	GENERATED_BODY()

public:
	ABaseBuilding();
	virtual void BeginPlay() override;

	EBuildingType GetBuildingType() const { return BuildingType; }

	FTransform GetClosestEntryTransform(const FVector& FromLocation) const;
	FTransform GetBestExitTransform(const FVector& ToLocation) const;
	FTransform GetClosestPauseTransform(const FVector& FromLocation) const;
	
protected:
	EBuildingType BuildingType;

	TArray<TSubclassOf<AEntryPoint>> EntryPoints; // Entry point
	TArray<TSubclassOf<AExitPoint>> ExitPoints; // Exit point
	TArray<TSubclassOf<APausePoint>> PausePoints; // Pause points for buildings with no need to enter/exit

private:
	void GatherInOutPoints();

};
