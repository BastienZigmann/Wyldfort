// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EBuildingType : uint8
{
	None,
	House,
	Well,
	FoodMarket,
	RessourceGathering,
	RessourceProcessing,
	Storage
};

UENUM(BlueprintType)
enum class EBuildingInteractionType : uint8
{
	None,
	Enter, // Come to the building, enter and disappear in it
	Wait, // Come to pause point, wait (interact or whatever)
	Gather // Come to entry, then leave to do its job for instance
};