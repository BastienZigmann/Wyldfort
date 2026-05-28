// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Bases/BaseGatheringBuilding.h"
#include "WoodCuttingCamp.generated.h"

// Scan surrounding foliage instances to find gatherable trees
// Keep a pool of found trees to assign to workers
UCLASS()
class WYLDFORT_API AWoodCuttingCamp : public ABaseGatheringBuilding
{
	GENERATED_BODY()
	
public:
	AWoodCuttingCamp();
	
};
