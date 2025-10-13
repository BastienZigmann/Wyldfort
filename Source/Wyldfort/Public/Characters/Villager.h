// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Bases/BaseCharacter.h"
#include "Villager.generated.h"

class ABaseBuilding;

UCLASS()
class WYLDFORT_API AVillager : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AVillager();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	void OnMoveCompleted();
	void OnMoveFailed(); 
private:
	
	void StartInitialMove();
	void PickNextDestination();
	void MoveToDestination();

	float Hunger;
	float Thirst;
	float Fatigue;

	ABaseBuilding* CurrentDestination;

};
