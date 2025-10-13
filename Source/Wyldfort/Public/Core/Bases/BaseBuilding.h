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

	FTransform GetDestinationTransform(const FVector& FromLocation) const; // Call to get entry point, no matter the type
	FTransform GetExitTransform(const FVector& ToLocation) const; // Call to get exit point, no matter the type
	
protected:
	EBuildingType BuildingType;
	EBuildingInteractionType BuildingInteractionType;
	
	FTransform GetClosestEntryTransform(const FVector& FromLocation) const;
	FTransform GetBestExitTransform(const FVector& ToLocation) const;
	FTransform GetClosestPauseTransform(const FVector& FromLocation) const;

	TArray<TWeakObjectPtr<AEntryPoint>> EntryPoints; // Entry point
	TArray<TWeakObjectPtr<AExitPoint>> ExitPoints; // Exit point
	TArray<TWeakObjectPtr<APausePoint>> PausePoints; // Pause points for buildings with no need to enter/exit

private:
	void GatherInOutPoints();

};
