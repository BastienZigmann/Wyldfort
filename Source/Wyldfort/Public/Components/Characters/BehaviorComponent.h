// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Bases/Components/BaseActorComponent.h"
#include "BehaviorComponent.generated.h"

class UBaseBehaviorState;

UCLASS()
class WYLDFORT_API UBehaviorComponent : public UBaseActorComponent
{
	GENERATED_BODY()
	
public:
	UBehaviorComponent();

	

	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	TObjectPtr<UBaseBehaviorState> CurrentState;

};
