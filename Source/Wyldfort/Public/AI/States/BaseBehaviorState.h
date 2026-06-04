// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseBehaviorState.generated.h"

class ABaseActor;

UCLASS()
class WYLDFORT_API UBaseBehaviorState : public UObject
{
	GENERATED_BODY()
	
public:
	UBaseBehaviorState() {};
	void Init(ABaseActor* InOwner) { Owner = InOwner; };
	virtual void Enter() {};
	virtual void Update(float DeltaTime) {};
	virtual void Exit() {};
	
protected:
	template<typename T>
	T* GetOwner() const {return Cast<T>(Owner);}
	
	enum class ESubState : uint8 {NONE, GOTO, DO, GO_BACK};
	ESubState SubState = ESubState::NONE;

private:
	UPROPERTY()
	TObjectPtr<ABaseActor> Owner;

};
