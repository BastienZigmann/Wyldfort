// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Bases/Components/BaseActorComponent.h"
#include "NeedsComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNeedCritical);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnNeedValueChanged, float);

UCLASS()
class WYLDFORT_API UNeedsComponent : public UBaseActorComponent
{
	GENERATED_BODY()

public:
	UNeedsComponent();

	void Feed(const float Amount = 0);
	void Drink(const float Amount = 0);

	FOnNeedCritical OnHungerCritical; // Behavior trigger
	FOnNeedCritical OnThirstCritical; // Behavior trigger

	FOnNeedValueChanged OnHungerChanged; // For UI display
	FOnNeedValueChanged OnThirstChanged; // for UI display

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float Hunger = 100.0f;
	float Thirst = 100.0f;

	bool bHungerCriticalFired = false;
	bool bThirstCriticalFired = false;

	UPROPERTY(EditDefaultsOnly, Category = "Needs")
    float DecayRate = 2.0f; // units per second, high for testing

    UPROPERTY(EditDefaultsOnly, Category = "Needs")
    float CriticalThreshold = 20.0f;
	
};
