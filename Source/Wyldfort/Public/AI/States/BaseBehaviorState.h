// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseBehaviorState.generated.h"

class ABaseCharacter;
struct FStatesTransitionInfo;

UCLASS()
class WYLDFORT_API UBaseBehaviorState : public UObject
{
	GENERATED_BODY()
	
public:
	UBaseBehaviorState() {};
	void Init(ABaseCharacter* InOwner) { Owner = InOwner; };
	virtual void Enter() { bIn = true;};
	virtual void Update(float DeltaTime) { if(!bIn) return;};
	virtual void Exit() {bIn = false;};
	virtual UBaseBehaviorState* HandleTransition(const FStatesTransitionInfo& transitionInfo) const {return nullptr;} ;
	virtual UBaseBehaviorState* GetNextState() const {return nullptr;};
	
protected:
	template<typename T>
	T* GetOwner() const {return Cast<T>(Owner);}
	
	enum class ESubState : uint8 {NONE, GOTO, DO, GO_BACK};
	ESubState SubState = ESubState::NONE;

private:
	UPROPERTY()
	TObjectPtr<ABaseCharacter> Owner;

	bool bIn = false; // has entered and haven't exited
};
