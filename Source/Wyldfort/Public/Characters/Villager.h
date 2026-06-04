// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
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

	UVillagerMovementComponent* GetVillagerMovementComponent() const { return VillagerMovementComponent; };
	void SetWorkBuilding(ABaseBuilding* Building);
	
private:

	UPROPERTY()
	TObjectPtr<UVillagerMovementComponent> VillagerMovementComponent;

	UPROPERTY()
	TObjectPtr<ABaseBuilding> Work = nullptr;

};
