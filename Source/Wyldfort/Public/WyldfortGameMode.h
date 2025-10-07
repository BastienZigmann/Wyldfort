// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WyldfortGameMode.generated.h"

/**
 * 
 */
UCLASS()
class WYLDFORT_API AWyldfortGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AWyldfortGameMode();

protected:
	virtual void StartPlay() override;
	virtual void BeginPlay() override;
	
};
