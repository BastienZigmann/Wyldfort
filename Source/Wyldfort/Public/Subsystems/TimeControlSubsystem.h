// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TimeControlSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class WYLDFORT_API UTimeControlSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	void SetPaused(bool bPaused);
	void SetSpeed(float NewSpeed);
	
	bool IsPaused() const { return bIsPaused; }
	float GetSpeed() const { return Speed; }

private:
	bool bIsPaused = false;

	float Speed = 1.0f;

	void ApplyTimeDilation(float Multiplier);
	
};
