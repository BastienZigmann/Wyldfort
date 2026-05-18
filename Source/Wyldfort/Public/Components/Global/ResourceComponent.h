// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Bases/Components/BaseActorComponent.h"
#include "Core/Types/ResourceTypes.h"
#include "ResourceComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDepleted);

/**
 * Resource component to put on resource node
 */
UCLASS()
class WYLDFORT_API UResourceComponent : public UBaseActorComponent
{
	GENERATED_BODY()

public:
	UResourceComponent();

	FResourceStack Gather();

	int32 GetAvailableAmount() const { return TotalAmount; }
	float GetGatherDuration() const { return GatherDuration; }
	bool IsDepleted() const { return bDepleted; }

	FOnDepleted OnDepleted;

private:
	EResourceType Type;
	int32 TotalAmount;
	int32 AmountPerGather;
	float GatherDuration;
	bool bDepleted = false;
};
