// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Bases/BaseSubsystem.h"
#include "VillagerManagerSubsystem.generated.h"

class AVillager;

/**
 * 
 */
UCLASS()
class WYLDFORT_API UVillagerManagerSubsystem : public UBaseSubsystem
{
	GENERATED_BODY()
	
public:
	UVillagerManagerSubsystem();

	void RegisterVillager(class AVillager* Villager);
	void UnregisterVillager(class AVillager* Villager);

	TArray<AVillager*> GetUnemployedVillagers();

private:
	TArray<TWeakObjectPtr<AVillager>> RegisteredVillager;

};
