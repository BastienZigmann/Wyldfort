// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Bases/BaseBuilding.h"
#include "WoodCuttingCamp.generated.h"

class ARessourceNode;

// UFoliageInstancedStaticMeshComponent Has many instance, when removing one, the last in the list is moved at the index of the removed one.
// So when saving it, NeedUpdateIfRemoval is true if it's the last, meaning it would need update
struct FInstanceRef
{
	int32 InstanceIndex = INDEX_NONE;
	FGuid ComponentGuid;
	FVector Location;
	bool NeedUpdateIfRemoval = false;
	// TODO Way to differenciate the many different trees types (UFoliageInstancedStaticMeshComponent)

	ARessourceNode* Node = nullptr;

	bool operator==(const FInstanceRef& Other) const
	{
		return ComponentGuid == Other.ComponentGuid && InstanceIndex == Other.InstanceIndex;	
	};

};

FORCEINLINE uint32 GetTypeHash(const FInstanceRef& K)
{
    // fold parts into 32-bit hash
    uint32 Hash1 = GetTypeHash(K.ComponentGuid.A) ^ GetTypeHash(K.ComponentGuid.B) ^ GetTypeHash(K.ComponentGuid.C) ^ GetTypeHash(K.ComponentGuid.D);
    return HashCombine(Hash1, ::GetTypeHash(K.InstanceIndex));
}

// Scan surrounding foliage instances to find gatherable trees
// Keep a pool of found trees to assign to workers
UCLASS()
class WYLDFORT_API AWoodCuttingCamp : public ABaseBuilding
{
	GENERATED_BODY()
	
public:
	AWoodCuttingCamp();

	UPROPERTY(EditAnywhere, Category = "Wood Cutting Camp")
	float ScanRadius = 2000.f;
	
	UPROPERTY(EditAnywhere, Category = "Wood Cutting Camp")
	float ScanInterval = 10.f;

	void RemoveTree(int InstanceIdx);
	void SetNumberOfWorkerAssigned(int32 Value);

private:
	virtual void BeginPlay() override;

private:

	FTimerHandle ScanTimerHandle;

	int32 NumberOfWorkerAssigned = 0;

	TSet<FInstanceRef> TreePool;

	void ScanArea(); // Scan an circular area to detect trees in range

};
