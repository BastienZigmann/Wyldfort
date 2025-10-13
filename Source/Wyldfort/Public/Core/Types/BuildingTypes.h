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
	Ressource,
	Industry,
	Storage
};

UENUM(BlueprintType)
enum class EBuildingInteractionType : uint8
{
	None,
	Enter,
	Wait,
	Gather
};