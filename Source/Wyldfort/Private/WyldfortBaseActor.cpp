// Fill out your copyright notice in the Description page of Project Settings.


#include "WyldfortBaseActor.h"

// Sets default values
AWyldfortBaseActor::AWyldfortBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWyldfortBaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWyldfortBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

