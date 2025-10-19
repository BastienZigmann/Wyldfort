// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Bases/Components/BaseActorComponent.h"
#include "Characters/Villager.h"
#include "BaseVillagerComponent.generated.h"

UCLASS()
class WYLDFORT_API UBaseVillagerComponent : public UBaseActorComponent
{
	GENERATED_BODY()
	
public:
	UBaseVillagerComponent();

protected:
	void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<AVillager> OwningVillager;

	AVillager* GetOwningVillager();
};
