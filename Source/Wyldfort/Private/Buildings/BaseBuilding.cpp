// Fill out your copyright notice in the Description page of Project Settings.

#include "Buildings/BaseBuilding.h"
#include "Buildings/Parts/EntryPoint.h"
#include "Buildings/Parts/ExitPoint.h"
#include "Buildings/Parts/PausePoint.h"

ABaseBuilding::ABaseBuilding()
{
    PrimaryActorTick.bCanEverTick = false;

    BuildingType = EBuildingType::None;

    EnableDebug();
}

void ABaseBuilding::BeginPlay()
{
    Super::BeginPlay();

    GatherInOutPoints();
}

void ABaseBuilding::GatherInOutPoints()
{
    TArray<AActor*> FoundActors;
    GetAttachedActors(FoundActors);
    
    for (AActor* Actor : FoundActors)
    {
        if (AEntryPoint* EntryPoint = Cast<AEntryPoint>(Actor))
        {
            EntryPoints.Add(EntryPoint->GetClass());
        }
        else if (AExitPoint* ExitPoint = Cast<AExitPoint>(Actor))
        {
            ExitPoints.Add(ExitPoint->GetClass());
        }
        else if (APausePoint* PausePoint = Cast<APausePoint>(Actor))
        {
            PausePoints.Add(PausePoint->GetClass());
        }
        else
        {
            WarningLog(FString::Printf(TEXT("Actor %s has tag 'Entry' but is not of type AEntryPoint."), *Actor->GetName()), this);
        }
    }

    if (EntryPoints.Num() == 0)
    {
        WarningLog("No entry points found for building.", this);
    }
    else
    {
        DebugLog(FString::Printf(TEXT("Found %d entry points."), EntryPoints.Num()), this);
    }
}