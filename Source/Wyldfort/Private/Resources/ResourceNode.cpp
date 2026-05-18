// Fill out your copyright notice in the Description page of Project Settings.


#include "Resources/ResourceNode.h"
#include "Components/Global/ResourceComponent.h"

// Sets default values
AResourceNode::AResourceNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ResourceComponent = CreateDefaultSubobject<UResourceComponent>(TEXT("ResourceComponent"));

}