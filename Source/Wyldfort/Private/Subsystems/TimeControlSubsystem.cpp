// Fill out your copyright notice in the Description page of Project Settings.

#include "Subsystems/TimeControlSubsystem.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"

void UTimeControlSubsystem::Tick(float DeltaTime)
{
    if (!GetWorld()) return;

    const double now = GetWorld()->GetRealTimeSeconds();
    if (LastTime <= 0.) LastTime = now; // Initial Case
    DeltaSeconds = static_cast<float>(LastTime - now);
    LastTime = now;

}

void UTimeControlSubsystem::RegisterTimeAffected(AActor* Actor)
{
    if (!Actor) return;
    TimeAffectedActors.Add(Actor);
    ApplyToActor(Actor);
}

void UTimeControlSubsystem::UnregisterTimeAffected(AActor* Actor)
{
    if (!Actor) return;
    TimeAffectedActors.Remove(Actor);

    // Optional: restore defaults
    if(IsValid(Actor))
    {
        Actor->CustomTimeDilation = 1.f;
        if (AAIController* AI = Cast<AAIController>(Actor->GetInstigatorController()))
		{
			if (UBrainComponent* Brain = AI->BrainComponent) { Brain->ResumeLogic(TEXT("Unregister")); }
		}
		for (UActorComponent* C : Actor->GetComponents())
		{
            if (USkeletalMeshComponent* Skel = Cast<USkeletalMeshComponent>(C))
			{
                Skel->bPauseAnims = false;
                Skel->GlobalAnimRateScale = 1.f;
            }
		}
    }
}

void UTimeControlSubsystem::SetPaused(bool bInPaused)
{
    if (bInPaused == bIsPaused) return; // No change needed, already paused
    bIsPaused = bInPaused;

    ApplyToActors();
    OnPauseChanged.Broadcast(bIsPaused);
}

void UTimeControlSubsystem::SetSpeed(float InSpeed)
{
    if (InSpeed == Speed) return; // No change needed, same speed
    InSpeed = FMath::Clamp(InSpeed, 0.1f, 4.0f);
    Speed = InSpeed;

    ApplyToActors();
    OnSpeedChanged.Broadcast(Speed);
}

void UTimeControlSubsystem::ApplyToActors() 
{

    for (auto It = TimeAffectedActors.CreateIterator(); It; ++It)
    {
        if (AActor* Actor = It->Get())
        {
            ApplyToActor(Actor);
        }
        else
        {
            It.RemoveCurrent(); // Cleanup dead Refs
        }
    }

}

void UTimeControlSubsystem::ApplyToActor(AActor* Actor) const
{
    if (!Actor || ! IsValid(Actor)) return;

    const float TargetDilation = bIsPaused ? 0.f : FMath::Max(0.f, Speed);
	Actor->CustomTimeDilation = TargetDilation;

    // Optional CPU saving: pause Behavior Trees when paused
	if (AAIController* AI = Cast<AAIController>(Actor->GetInstigatorController()))
	{
		if (UBrainComponent* Brain = AI->BrainComponent)
		{
			if (bIsPaused) Brain->PauseLogic(TEXT("GamePaused"));
			else         Brain->ResumeLogic(TEXT("Unpaused"));
		}
	}

    // Optional: stop movement component updates while paused (saves work)
	if (bIsPaused)
	{
		if (ACharacter* Char = Cast<ACharacter>(Actor))
		{
			if (UCharacterMovementComponent* Move = Char->GetCharacterMovement())
			{
				Move->Deactivate();
			}
			for (UActorComponent* C : Actor->GetComponents())
			{
                if (USkeletalMeshComponent* Skel = Cast<USkeletalMeshComponent>(C))
                {
                    Skel->bPauseAnims = true;
                    Skel->GlobalAnimRateScale = 0.f;
                }
			}
		}
	}
	else
	{
		if (ACharacter* Char = Cast<ACharacter>(Actor))
		{
			if (UCharacterMovementComponent* Move = Char->GetCharacterMovement())
			{
				Move->Activate(true);
			}
			for (UActorComponent* C : Actor->GetComponents())
			{
                if (USkeletalMeshComponent* Skel = Cast<USkeletalMeshComponent>(C))
                {
                    Skel->bPauseAnims = false;
                    Skel->GlobalAnimRateScale = 1.f;
                }
			}
		}
	}

}