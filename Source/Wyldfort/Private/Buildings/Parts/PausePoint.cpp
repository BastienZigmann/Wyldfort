// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/Parts/PausePoint.h"

// Sets default values
APausePoint::APausePoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APausePoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APausePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

