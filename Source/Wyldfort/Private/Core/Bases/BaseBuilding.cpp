// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/Bases/BaseBuilding.h"
#include "Buildings/Parts/EntryPoint.h"
#include "Buildings/Parts/ExitPoint.h"
#include "Buildings/Parts/PausePoint.h"
#include "Subsystems/VillageManagerSubsystem.h"

ABaseBuilding::ABaseBuilding()
{
    PrimaryActorTick.bCanEverTick = false;

    BuildingType = EBuildingType::None;
    BuildingInteractionType = EBuildingInteractionType::None; // Default to None

    EnableDebug();
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
            EntryPoints.Add(EntryPoint);
        else if (AExitPoint* ExitPoint = Cast<AExitPoint>(Actor))
            ExitPoints.Add(ExitPoint);
        else if (APausePoint* PausePoint = Cast<APausePoint>(Actor))
            PausePoints.Add(PausePoint);
    }

    if (EntryPoints.Num() == 0)
        DebugLog("No entry points found for building.", this);
    else
        DebugLog(FString::Printf(TEXT("Found %d entry points for building."), EntryPoints.Num()), this);
    if (ExitPoints.Num() == 0)
        DebugLog("No exit points found for building.", this);
    else
        DebugLog(FString::Printf(TEXT("Found %d exit points for building."), ExitPoints.Num()), this);
    if (PausePoints.Num() == 0)
        DebugLog("No pause points found for building.", this);
    else
        DebugLog(FString::Printf(TEXT("Found %d pause points for building."), PausePoints.Num()), this);
}

FTransform ABaseBuilding::GetDestinationTransform(const FVector& FromLocation) const
{
    switch (BuildingInteractionType)
    {
        case EBuildingInteractionType::Enter:
        case EBuildingInteractionType::Gather:
            DebugLog("Getting entry transform.", this);
            DebugLog("Entry points available: " + FString::FromInt(EntryPoints.Num()), this);
            DebugLog("From location: " + FromLocation.ToString(), this);
            DebugLog("Closest entry transform: " + GetClosestEntryTransform(FromLocation).GetLocation().ToString(), this);
            return GetClosestEntryTransform(FromLocation);
        case EBuildingInteractionType::Wait:
            DebugLog("Getting pause transform.", this);
            return GetBestExitTransform(FromLocation);
        default:
            DebugLog("Invalid building interaction type.", this);
            return FTransform::Identity;
    }
}

FTransform ABaseBuilding::GetExitTransform(const FVector& ToLocation) const
{
    return GetBestExitTransform(ToLocation);
}

FTransform ABaseBuilding::GetClosestEntryTransform(const FVector& FromLocation) const
{
    FTransform ClosestTransform;
    float ClosestDistanceSqr = TNumericLimits<float>::Max();
    
    for (TWeakObjectPtr<AEntryPoint> EntryPointPtr : EntryPoints)
    {
        if (AEntryPoint* EntryPoint = EntryPointPtr.Get())
        {
            float DistanceSqr = FVector::DistSquared(FromLocation, EntryPoint->GetActorLocation());
            if (DistanceSqr < ClosestDistanceSqr)
            {
                ClosestDistanceSqr = DistanceSqr;
                ClosestTransform = EntryPoint->GetActorTransform();
                DebugLog(FString::Printf(TEXT("New closest entry point found")), this);
            }
        }
    }
    
    return ClosestTransform;
}

FTransform ABaseBuilding::GetBestExitTransform(const FVector& ToLocation) const
{
    FTransform BestTransform;
    float BestScore = -1.0f;

    for (TWeakObjectPtr<AExitPoint> ExitPointPtr : ExitPoints)
    {
        if (AExitPoint* ExitPoint = ExitPointPtr.Get())
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
    for (TWeakObjectPtr<APausePoint> PausePointPtr : PausePoints)
    {
        if (APausePoint* PausePoint = PausePointPtr.Get())
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
