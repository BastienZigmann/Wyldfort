// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Bases/Components/BaseActorComponent.h"
#include "Core/Types/RessourceTypes.h"
#include "InventoryComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WYLDFORT_API UInventoryComponent : public UBaseActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	void AddRessource(ERessourceType r, int32 quantity, bool ShouldNotifyGlobalStock = true);
	void RemoveRessource(ERessourceType r, int32 quantity, bool ShouldNotifyGlobalStock = true);
	void TransferRessourceTo(AActor* other, ERessourceType r, int32 quantity);

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(Transient)
	TMap<ERessourceType, int> Inventory;
		
};
