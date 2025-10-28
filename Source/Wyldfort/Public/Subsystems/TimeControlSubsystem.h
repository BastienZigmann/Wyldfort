// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TimeControlSubsystem.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGamePausedChanged, bool); // Pause status change delegate
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameSpeedChanged, float); // Speed change delegate

UCLASS()
class WYLDFORT_API UTimeControlSubsystem : public UWorldSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

public:
	void SetPaused(bool bInPaused);
	void SetSpeed(float InSpeed);
	
	bool IsPaused() const { return bIsPaused; }
	float GetSpeed() const { return Speed; }

	void RegisterTimeAffected(AActor* Actor);
	void UnregisterTimeAffected(AActor* Actor);

	FOnGamePausedChanged OnPauseChanged;
	FOnGameSpeedChanged OnSpeedChanged;

	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UGameTimeSubsystem, STATGROUP_Tickables); }
	virtual bool IsTickable() const override { return true; }

private:
	void ApplyToActors();
	void ApplyToActor(AActor* Actor) const;

	bool bIsPaused = false;
	float Speed = 1.0f;

	double LastTime = 0.0;
	float DeltaSeconds = 0.f;

	UPROPERTY(Transient)
	TSet<TWeakObjectPtr<AActor>> TimeAffectedActors;
	
};
