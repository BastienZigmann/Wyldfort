// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Bases/Components/BaseActorComponent.h"
#include "Resources/ResourceTypes.h"
#include "InventoryComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WYLDFORT_API UInventoryComponent : public UBaseActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	void AddResource(EResourceType r, int32 quantity, bool ShouldNotifyGlobalStock = true);
	void RemoveResource(EResourceType r, int32 quantity, bool ShouldNotifyGlobalStock = true);
	void TransferResourceTo(AActor* other, EResourceType r, int32 quantity);

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(Transient)
	TMap<EResourceType, int> Inventory;
		
};
