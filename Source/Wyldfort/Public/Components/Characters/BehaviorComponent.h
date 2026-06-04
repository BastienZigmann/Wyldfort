// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Bases/Components/BaseActorComponent.h"
#include "BehaviorComponent.generated.h"

class UBaseBehaviorState;
struct FStatesTransitionInfo;

UCLASS()
class WYLDFORT_API UBehaviorComponent : public UBaseActorComponent
{
	GENERATED_BODY()
	
public:
	UBehaviorComponent();
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OnCriticalStarving();
	void OnCriticalThirsty();

private:

	UPROPERTY()
	TObjectPtr<UBaseBehaviorState> CurrentState;
	void SetNewState(UBaseBehaviorState* NewState);

	void ComputeTransition(const FStatesTransitionInfo& transitionInfo);

};
