// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ResourceTypes.generated.h"

UENUM(BlueprintType)
enum class EResourceType : uint8
{
	None,
	Rock,
	Wood
};

USTRUCT()
struct FResourceStack
{
	GENERATED_BODY()

	EResourceType Type;
	int32 Quantity;
};
