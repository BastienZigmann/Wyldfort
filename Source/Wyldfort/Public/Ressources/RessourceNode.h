// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/Types/RessourceTypes.h"
#include "Core/Bases/BaseActor.h"
#include "RessourceNode.generated.h"

class UStaticMesh;

UCLASS()
class WYLDFORT_API ARessourceNode : public ABaseActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARessourceNode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	ERessourceType RessourceType = ERessourceType::None;
	int32 RessourceAmount = 100;
	int32 RessourcePerGather = 10;
	float GatherTime = 2.0f;

};
