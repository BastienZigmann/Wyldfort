// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/GameSpeedControlWidget.h"
#include "Components/Button.h"
#include "Subsystems/TimeControlSubsystem.h"
#include "Engine/World.h"

void UGameSpeedControlWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (PauseButton)
    {
        PauseButton->OnClicked.AddDynamic(this, &UGameSpeedControlWidget::OnPauseClicked);
    }
    if (PlayButton)
    {
        PlayButton->OnClicked.AddDynamic(this, &UGameSpeedControlWidget::OnPlayClicked);
    }
    if (Speed2Button)
    {
        Speed2Button->OnClicked.AddDynamic(this, &UGameSpeedControlWidget::OnSpeed2Clicked);
    }
    if (Speed3Button)
    {
        Speed3Button->OnClicked.AddDynamic(this, &UGameSpeedControlWidget::OnSpeed3Clicked);
    }
}

void UGameSpeedControlWidget::OnPauseClicked()
{
    if (UWorld* World = GetWorld())
    {
        if (UTimeControlSubsystem* TimeSubsystem = World->GetSubsystem<UTimeControlSubsystem>())
        {
            TimeSubsystem->SetPaused(true); // Pause the game
        }
    }
}

void UGameSpeedControlWidget::OnPlayClicked()
{
    if (UWorld* World = GetWorld())
    {
        if (UTimeControlSubsystem* TimeSubsystem = World->GetSubsystem<UTimeControlSubsystem>())
        {
            TimeSubsystem->SetPaused(false); // Unpause the game, normal speed
            TimeSubsystem->SetSpeed(1.0f);
        }
    }
}

void UGameSpeedControlWidget::OnSpeed2Clicked()
{
    if (UWorld* World = GetWorld())
    {
        if (UTimeControlSubsystem* TimeSubsystem = World->GetSubsystem<UTimeControlSubsystem>())
        {
            TimeSubsystem->SetPaused(false); // Unpause the game
            TimeSubsystem->SetSpeed(2.0f);   // Set speed to 2x
        }
    }
}

void UGameSpeedControlWidget::OnSpeed3Clicked()
{
    if (UWorld* World = GetWorld())
    {
        if (UTimeControlSubsystem* TimeSubsystem = World->GetSubsystem<UTimeControlSubsystem>())
        {
            TimeSubsystem->SetPaused(false); // Unpause the game
            TimeSubsystem->SetSpeed(3.0f);   // Set speed to 3x
        }
    }
}