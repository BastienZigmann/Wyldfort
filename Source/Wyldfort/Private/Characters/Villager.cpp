// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Villager.h"
#include "AI/Controllers/MovementAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/Characters/Villagers/VillagerMovementComponent.h"

AVillager::AVillager()
{
    // EnableDebug();
    PrimaryActorTick.bCanEverTick = false;

    AIControllerClass = AMovementAIController::StaticClass();

    VillagerMovementComponent = CreateDefaultSubobject<UVillagerMovementComponent>(TEXT("VillagerMovementComponent"));
    if (!VillagerMovementComponent) 
    {
        ErrorLog("Failed to create VillagerMovementComponent!", this);
        return;
    }

    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    GetCharacterMovement()->bOrientRotationToMovement = true; 
    DebugLog("Village initialized", this);
}

void AVillager::BeginPlay()
{
    Super::BeginPlay();
    
    DebugLog("Villager spawned.", this);
}

void AVillager::SetWorkBuilding(ABaseBuilding* Building) 
{ 
    Work = Building; 
}