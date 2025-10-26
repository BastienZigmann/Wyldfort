// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/TimeControlSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UTimeControlSubsystem::SetPaused(bool bPaused)
{
    if (bPaused == bIsPaused) return; // No change needed
    if (UWorld* World = GetWorld())
    {
        bIsPaused = bPaused;
        UGameplayStatics::SetGamePaused(GetWorld(), bIsPaused);

        if (!bIsPaused)
        {
            ApplyTimeDilation(Speed);
        }
    }
}

void UTimeControlSubsystem::SetSpeed(float NewSpeed)
{
    if (NewSpeed == Speed) return; // No change needed
    NewSpeed = FMath::Clamp(NewSpeed, 0.1f, 4.0f);
    Speed = NewSpeed;

    if (!bIsPaused)
    {
        ApplyTimeDilation(Speed);
    }
}

void UTimeControlSubsystem::ApplyTimeDilation(float Multiplier)
{
    if (UWorld* World = GetWorld())
    {
        World->GetWorldSettings()->SetTimeDilation(Multiplier);
    }
}