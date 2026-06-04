// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/Global/TimeAffectedComponent.h"
#include "Components/Global/InventoryComponent.h"
#include "Components/Characters/BehaviorComponent.h"
#include "Components/Characters/NeedsComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
    GetMesh()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	TimeAffectedComponent = CreateDefaultSubobject<UTimeAffectedComponent>(TEXT("TimeAffectedComponent"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	if (!InventoryComponent)
	{
		ErrorLog("Failed to create inventory component", this);
		return;
	}
    BehaviorComponent = CreateDefaultSubobject<UBehaviorComponent>(TEXT("BehaviorComponent"));
    if (!BehaviorComponent) 
    {
        ErrorLog("Failed to create BehaviorComponent", this);
        return;
    }
    NeedsComponent = CreateDefaultSubobject<UNeedsComponent>(TEXT("NeedsComponent"));
    if (!NeedsComponent) 
    {
        ErrorLog("Failed to create NeedsComponent", this);
        return;
    }
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

