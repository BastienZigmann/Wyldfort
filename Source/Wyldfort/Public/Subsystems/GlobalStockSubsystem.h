// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Bases/BaseSubsystem.h"
#include "Core/Types/RessourceTypes.h"
#include "GlobalStockSubsystem.generated.h"

// Centralized Inventory system, should be notified when a transfer happens in one of the inventory in the game (cf InventoryComponent.h)
// This subsystem only use is to gather information about global stock for display purpose

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRessourceAdded, ERessourceType, int); // Should be called when any inventory have a ressource added. (Params : Type and quandity)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRessourceRemoved, ERessourceType, int); // Should be called when any inventory have a ressource removed. (Params : Type and quandity)

UCLASS()
class WYLDFORT_API UGlobalStockSubsystem : public UBaseSubsystem
{
	GENERATED_BODY()

public:
	UGlobalStockSubsystem();

	TArray<ERessourceType> GetInventoryRessources() const;
	int32 GetInventoryValue(ERessourceType r) const;

	FOnRessourceAdded NotifyRessourceAdded;
	FOnRessourceRemoved NotifyRessourceRemoved;

private:
	UPROPERTY(Transient)
	TMap<ERessourceType, int> Inventory;

	UFUNCTION()
	void HandleNotifyRessourceAdded(ERessourceType ResourceType, int32 Amount);
	UFUNCTION()
	void HandleNotifyRessourceRemoved(ERessourceType ResourceType, int32 Amount);

};

