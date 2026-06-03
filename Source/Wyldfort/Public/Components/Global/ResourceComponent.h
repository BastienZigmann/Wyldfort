// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Bases/Components/BaseActorComponent.h"
#include "Resources/ResourceTypes.h"
#include "ResourceComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDepletedDelegate); 

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

	void BindOnDepleted(const FSimpleDelegate& Delegate) { OnDepleted.Add(Delegate); }

private:
	UPROPERTY(EditAnywhere, Category = "Resource")
	EResourceType Type;
	UPROPERTY(EditAnywhere, Category = "Resource")
	int32 TotalAmount;
	UPROPERTY(EditAnywhere, Category = "Resource")
	int32 AmountPerGather;
	UPROPERTY(EditAnywhere, Category = "Resource")
	float GatherDuration;
	bool bDepleted = false;

	/**
	 * Happens once only
	 */
	FOnDepletedDelegate OnDepleted;
};
