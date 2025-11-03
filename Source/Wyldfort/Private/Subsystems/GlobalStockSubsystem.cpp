// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/GlobalStockSubsystem.h"

UGlobalStockSubsystem::UGlobalStockSubsystem()
{
    // Bind delegate handlers
    NotifyRessourceAdded.AddUObject(this, &UGlobalStockSubsystem::HandleNotifyRessourceAdded);
    NotifyRessourceRemoved.AddUObject(this, &UGlobalStockSubsystem::HandleNotifyRessourceRemoved);
}

TArray<ERessourceType> UGlobalStockSubsystem::GetInventoryRessources() const
{
    TArray<ERessourceType> Keys;
    Inventory.GetKeys(Keys);
    return Keys;
}

int32 UGlobalStockSubsystem::GetInventoryValue(ERessourceType r) const
{
    return Inventory.Contains(r) ? Inventory[r] : 0;
}

void UGlobalStockSubsystem::HandleNotifyRessourceAdded(ERessourceType r, int quantity)
{
    if (quantity <= 0)
    {
        ErrorLog("Got Notified of a <= 0 ressource Adding", this);
        return;
    }
    Inventory.Add(r, quantity);
}

void UGlobalStockSubsystem::HandleNotifyRessourceRemoved(ERessourceType r, int quantity)
{
    if (quantity <= 0)
    {
        ErrorLog("Got Notified of a <= 0 ressource removal", this);
        return;
    }
    Inventory[r] = FMath::Max(0, Inventory[r] - quantity);
}


