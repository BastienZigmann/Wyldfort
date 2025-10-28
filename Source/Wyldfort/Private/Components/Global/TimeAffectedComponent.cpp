// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Global/TimeAffectedComponent.h"
#include "Subsystems/TimeControlSubsystem.h"

void UTimeAffectedComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* World = GetWorld())
	{
		if (UTimeControlSubsystem* TimeControl = World->GetSubsystem<UTimeControlSubsystem>())
		{
			TimeControl->RegisterTimeAffected(GetOwner());
		}
	}
	
}

void UTimeAffectedComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UWorld* World = GetWorld())
	{
		if (UTimeControlSubsystem* TimeControl = World->GetSubsystem<UTimeControlSubsystem>())
		{
			TimeControl->UnregisterTimeAffected(GetOwner());
		}
	}
	Super::EndPlay(EndPlayReason);
}

