// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatesTransitionInfo.generated.h"

USTRUCT()
struct FStatesTransitionInfo
{
	GENERATED_BODY()

	bool isCriticalHungry = false;
	bool isCriticalThirst = false;
};

