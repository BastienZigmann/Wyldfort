// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Core/Utils/Logger.h"
#include "BaseCharacter.generated.h"

class UInventoryComponent;
class UTimeAffectedComponent;
class UBehaviorComponent;
class UNeedsComponent;

UCLASS()
class WYLDFORT_API ABaseCharacter : public ACharacter, public FLogger
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	UInventoryComponent* GetInventoryComponent() {return InventoryComponent;}
	UBehaviorComponent* GetBehaviorComponent() const { return BehaviorComponent; };
	UNeedsComponent* GetNeedsComponent() const { return NeedsComponent; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	UPROPERTY()
	TObjectPtr<UInventoryComponent> InventoryComponent;
	UPROPERTY()
	TObjectPtr<UTimeAffectedComponent> TimeAffectedComponent;
	UPROPERTY()
	TObjectPtr<UBehaviorComponent> BehaviorComponent;
	UPROPERTY()
	TObjectPtr<UNeedsComponent> NeedsComponent;

};
