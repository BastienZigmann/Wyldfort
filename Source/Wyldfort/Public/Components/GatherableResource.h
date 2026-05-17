// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FoliageInstancedStaticMeshComponent.h"
#include "Core/Types/ResourceTypes.h"
#include "GatherableResource.generated.h"

UCLASS()
class WYLDFORT_API UGatherableResource : public UFoliageInstancedStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UGatherableResource();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	EResourceType ResourceType = EResourceType::None;

	// Persistent unique id for this component (saved with level). Use for registries & saves.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource", meta=(ExposeOnSpawn=true))
    FGuid ComponentGuid;

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	virtual void OnRegister() override;

};
