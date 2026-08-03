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
	virtual void EndPlay(const EEndPlayReason::Type Reason) override;

	UVillagerMovementComponent* GetVillagerMovementComponent() const { return VillagerMovementComponent; };
	void SetWorkBuilding(ABaseBuilding* Building);
	const ABaseBuilding* GetWorkBuilding() const {return Work;};
	const bool HasWork() const {return GetWorkBuilding() != nullptr;};

private:

	UPROPERTY()
	TObjectPtr<UVillagerMovementComponent> VillagerMovementComponent;

	UPROPERTY()
	TObjectPtr<ABaseBuilding> Work = nullptr;

};
