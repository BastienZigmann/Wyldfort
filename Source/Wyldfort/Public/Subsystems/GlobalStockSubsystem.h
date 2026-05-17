// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Bases/BaseSubsystem.h"
#include "Core/Types/ResourceTypes.h"
#include "GlobalStockSubsystem.generated.h"

// Centralized Inventory system, should be notified when a transfer happens in one of the inventory in the game (cf InventoryComponent.h)
// This subsystem only use is to gather information about global stock for display purpose

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnResourceAdded, EResourceType, int); // Should be called when any inventory have a Resource added. (Params : Type and quandity)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnResourceRemoved, EResourceType, int); // Should be called when any inventory have a Resource removed. (Params : Type and quandity)

UCLASS()
class WYLDFORT_API UGlobalStockSubsystem : public UBaseSubsystem
{
	GENERATED_BODY()

public:
	UGlobalStockSubsystem();

	TArray<EResourceType> GetInventoryResources() const;
	int32 GetInventoryValue(EResourceType r) const;

	FOnResourceAdded NotifyResourceAdded;
	FOnResourceRemoved NotifyResourceRemoved;

private:
	UPROPERTY(Transient)
	TMap<EResourceType, int> Inventory;

	UFUNCTION()
	void HandleNotifyResourceAdded(EResourceType ResourceType, int32 Amount);
	UFUNCTION()
	void HandleNotifyResourceRemoved(EResourceType ResourceType, int32 Amount);

};

