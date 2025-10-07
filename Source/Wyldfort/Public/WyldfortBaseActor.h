// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utils/Logger.h"
#include "WyldfortBaseActor.generated.h"

UCLASS()
class WYLDFORT_API AWyldfortBaseActor : public AActor, public FLogger
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWyldfortBaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
