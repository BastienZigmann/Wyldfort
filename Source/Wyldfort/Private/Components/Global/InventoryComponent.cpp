// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Global/InventoryComponent.h"
#include "Subsystems/GlobalStockSubsystem.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::AddRessource(ERessourceType r, int32 quantity, bool ShouldNotifyGlobalStock)
{
	UWorld* World = GetWorld();
    if (!World) return;
	UGlobalStockSubsystem* GlobalStock = World->GetSubsystem<UGlobalStockSubsystem>();
	if (!GlobalStock && ShouldNotifyGlobalStock) // If we don't want to notify
	{
		ErrorLog("GlobalStock Subsystem missing, ressource adding cancelled", this);
		return;
	}
		
	if (quantity <= 0) 
	{
		ErrorLog("Adding quantity <= 0", this);
		return;
	}
    Inventory.Add(r, quantity);
	if (ShouldNotifyGlobalStock) 
		GlobalStock->NotifyRessourceAdded.Broadcast(r, quantity);
}

void UInventoryComponent::RemoveRessource(ERessourceType r, int32 quantity, bool ShouldNotifyGlobalStock)
{
	UWorld* World = GetWorld();
    if (!World) return;
	UGlobalStockSubsystem* GlobalStock = World->GetSubsystem<UGlobalStockSubsystem>();
	if (!GlobalStock && ShouldNotifyGlobalStock) 
	{
		ErrorLog("GlobalStock Subsystem missing, ressource removing cancelled", this);
		return;
	}
	
	if (quantity <= 0) 
	{
		ErrorLog("Removing quantity <= 0", this);
		return;
	}
    if (!Inventory.Contains(r))
    {
        ErrorLog("Removing Resssources from city inventory that doesn't exists", this);
        return;
    }
    Inventory[r] = FMath::Max(0, Inventory[r] - quantity);
	if (ShouldNotifyGlobalStock)
		GlobalStock->NotifyRessourceRemoved.Broadcast(r, quantity);
}

void UInventoryComponent::TransferRessourceTo(AActor* other, ERessourceType r, int32 quantity)
{
	if (!other) return;
	
	UInventoryComponent* otherInventory = other->FindComponentByClass<UInventoryComponent>();
	if (!otherInventory) 
	{
		ErrorLog("No valid inventory component transfer cancelled", this);
		return;
	}

	this->RemoveRessource(r, quantity, false);
	otherInventory->AddRessource(r, quantity, false);
}