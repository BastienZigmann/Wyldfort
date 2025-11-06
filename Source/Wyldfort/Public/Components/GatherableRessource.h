// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FoliageInstancedStaticMeshComponent.h"
#include "Core/Types/RessourceTypes.h"
#include "GatherableRessource.generated.h"

UCLASS()
class WYLDFORT_API UGatherableRessource : public UFoliageInstancedStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UGatherableRessource();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ressource")
	ERessourceType RessourceType = ERessourceType::None;

	// Persistent unique id for this component (saved with level). Use for registries & saves.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ressource", meta=(ExposeOnSpawn=true))
    FGuid ComponentGuid;

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	virtual void OnRegister() override;

};
