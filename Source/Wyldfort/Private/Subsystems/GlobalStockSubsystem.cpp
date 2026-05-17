// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/GlobalStockSubsystem.h"

UGlobalStockSubsystem::UGlobalStockSubsystem()
{
    // Bind delegate handlers
    NotifyResourceAdded.AddUObject(this, &UGlobalStockSubsystem::HandleNotifyResourceAdded);
    NotifyResourceRemoved.AddUObject(this, &UGlobalStockSubsystem::HandleNotifyResourceRemoved);
}

TArray<EResourceType> UGlobalStockSubsystem::GetInventoryResources() const
{
    TArray<EResourceType> Keys;
    Inventory.GetKeys(Keys);
    return Keys;
}

int32 UGlobalStockSubsystem::GetInventoryValue(EResourceType r) const
{
    return Inventory.Contains(r) ? Inventory[r] : 0;
}

void UGlobalStockSubsystem::HandleNotifyResourceAdded(EResourceType r, int quantity)
{
    if (quantity <= 0)
    {
        ErrorLog("Got Notified of a <= 0 Resource Adding", this);
        return;
    }
    Inventory.Add(r, quantity);
}

void UGlobalStockSubsystem::HandleNotifyResourceRemoved(EResourceType r, int quantity)
{
    if (quantity <= 0)
    {
        ErrorLog("Got Notified of a <= 0 Resource removal", this);
        return;
    }
    Inventory[r] = FMath::Max(0, Inventory[r] - quantity);
}


