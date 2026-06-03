// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Resources/ResourceTypes.h"
#include "Core/Bases/BaseActor.h"
#include "ResourceNode.generated.h"

class UStaticMesh;
class UResourceComponent;

UCLASS()
class WYLDFORT_API AResourceNode : public ABaseActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourceNode();

	UResourceComponent* GetResourceComponent() const { return ResourceComponent; }

private:
	UPROPERTY(VisibleAnywhere, Category = "Resource")
	TObjectPtr<UResourceComponent> ResourceComponent;

};
