// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/Types/ResourceTypes.h"
#include "Core/Bases/BaseActor.h"
#include "ResourceNode.generated.h"

class UStaticMesh;

UCLASS()
class WYLDFORT_API AResourceNode : public ABaseActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourceNode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	EResourceType ResourceType = EResourceType::None;
	int32 ResourceAmount = 100;
	int32 ResourcePerGather = 10;
	float GatherTime = 2.0f;

};
