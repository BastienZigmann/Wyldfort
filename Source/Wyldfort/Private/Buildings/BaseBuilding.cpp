// Fill out your copyright notice in the Description page of Project Settings.

#include "Buildings/BaseBuilding.h"
#include "Buildings/Parts/EntryPoint.h"
#include "Buildings/Parts/ExitPoint.h"
#include "Buildings/Parts/PausePoint.h"
#include "Subsystems/VillageManagerSubsystem.h"

ABaseBuilding::ABaseBuilding()
{
    PrimaryActorTick.bCanEverTick = false;

    BuildingType = EBuildingType::None;

    // EnableDebug();
}

void ABaseBuilding::BeginPlay()
{
    Super::BeginPlay();

    if (UWorld* World = GetWorld())
    {
        if (UVillageManagerSubsystem* Subsys = World->GetSubsystem<UVillageManagerSubsystem>())
        {
            Subsys->RegisterBuilding(this);
            DebugLog(FString::Printf(TEXT("Building of type %d registered."), static_cast<uint8>(BuildingType)), this);
        }
    }

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
    }

    if (EntryPoints.Num() == 0)
    {
        DebugLog("No entry points found for building.", this);
    }
    else
    {
        DebugLog(FString::Printf(TEXT("Found %d entry points for building."), EntryPoints.Num()), this);
    }
    if (ExitPoints.Num() == 0)
    {
        DebugLog("No exit points found for building.", this);
    }
    else
    {
        DebugLog(FString::Printf(TEXT("Found %d exit points for building."), ExitPoints.Num()), this);
    }
    if (PausePoints.Num() == 0)
    {
        DebugLog("No pause points found for building.", this);
    }
    else
    {
        DebugLog(FString::Printf(TEXT("Found %d pause points for building."), PausePoints.Num()), this);
    }
}

FTransform ABaseBuilding::GetClosestEntryTransform(const FVector& FromLocation) const
{
    FTransform ClosestTransform;
    float ClosestDistanceSqr = TNumericLimits<float>::Max();
    for (TSubclassOf<AEntryPoint> EntryClass : EntryPoints)
    {
        if (AEntryPoint* EntryPoint = EntryClass->GetDefaultObject<AEntryPoint>())
        {
            float DistanceSqr = FVector::DistSquared(FromLocation, EntryPoint->GetActorLocation());
            if (DistanceSqr < ClosestDistanceSqr)
            {
                ClosestDistanceSqr = DistanceSqr;
                ClosestTransform = EntryPoint->GetActorTransform();
            }
        }
    }
    return ClosestTransform;
}

FTransform ABaseBuilding::GetBestExitTransform(const FVector& ToLocation) const
{
    FTransform BestTransform;
    float BestScore = -1.0f;

    for (TSubclassOf<AExitPoint> ExitClass : ExitPoints)
    {
        if (AExitPoint* ExitPoint = ExitClass->GetDefaultObject<AExitPoint>())
        {
            float Score = FVector::DotProduct(ExitPoint->GetActorForwardVector(), (ToLocation - ExitPoint->GetActorLocation()).GetSafeNormal());
            if (Score > BestScore)
            {
                BestScore = Score;
                BestTransform = ExitPoint->GetActorTransform();
            }
        }
    }

    return BestTransform;
}

FTransform ABaseBuilding::GetClosestPauseTransform(const FVector& FromLocation) const
{
    FTransform ClosestTransform;
    float ClosestDistanceSqr = TNumericLimits<float>::Max();
    for (TSubclassOf<APausePoint> PauseClass : PausePoints)
    {
        if (APausePoint* PausePoint = PauseClass->GetDefaultObject<APausePoint>())
        {
            float DistanceSqr = FVector::DistSquared(FromLocation, PausePoint->GetActorLocation());
            if (DistanceSqr < ClosestDistanceSqr)
            {
                ClosestDistanceSqr = DistanceSqr;
                ClosestTransform = PausePoint->GetActorTransform();
            }
        }
    }
    return ClosestTransform;
}
