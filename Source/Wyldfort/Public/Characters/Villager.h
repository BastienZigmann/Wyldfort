// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Bases/BaseCharacter.h"
#include "Villager.generated.h"

class ABaseBuilding;
class UVillagerMovementComponent;

UCLASS()
class WYLDFORT_API AVillager : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AVillager();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UVillagerMovementComponent* GetVillagerMovementComponent() const { return VillagerMovementComponent; };
	
private:

	UPROPERTY()
	TObjectPtr<UVillagerMovementComponent> VillagerMovementComponent;
	
	void StartInitialMove();

	float Hunger;
	float Thirst;
	float Fatigue;

	

};
