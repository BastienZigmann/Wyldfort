// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Bases/Components/BaseVillagerComponent.h"
#include "VillagerMovementComponent.generated.h"

class ABaseBuilding;

UCLASS()
class WYLDFORT_API UVillagerMovementComponent : public UBaseVillagerComponent
{
	GENERATED_BODY()

public:
	UVillagerMovementComponent();

	void PickNextDestination();
	void MoveToDestination();
	void OnMoveCompleted(bool bSuccess = true);

	ABaseBuilding* CurrentDestination;

protected:
	void BeginPlay() override;



};
