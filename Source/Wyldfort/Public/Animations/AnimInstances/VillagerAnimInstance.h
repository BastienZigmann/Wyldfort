// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "VillagerAnimInstance.generated.h"

class AVillager;

UCLASS()
class WYLDFORT_API UVillagerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UVillagerAnimInstance();
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float Speed = 0;

private:
	AVillager* CachedOwningVillager;
	AVillager* TryGetSetOwningVillager();

};
