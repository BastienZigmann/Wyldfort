// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Bases/BaseBuilding.h"
#include "Core/Types/ResourceTypes.h"
#include "BaseGatheringBuilding.generated.h"

class AResourceNode;
class AVillager;

// UFoliageInstancedStaticMeshComponent Has many instance, when removing one, the last in the list is moved at the index of the removed one.
// So when saving it, NeedUpdateIfRemoval is true if it's the last, meaning it would need update
struct FInstanceRef
{
	int32 InstanceIndex = INDEX_NONE;
	FGuid ComponentGuid;
	FVector Location;
	bool NeedUpdateIfRemoval = false;
	// TODO Way to differenciate the many different resources types (UFoliageInstancedStaticMeshComponent)

	AResourceNode* Node = nullptr;

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

UCLASS()
class WYLDFORT_API ABaseGatheringBuilding : public ABaseBuilding
{
	GENERATED_BODY()

public:
	ABaseGatheringBuilding();

	// Scan
	UPROPERTY(EditAnywhere, Category = "Scan")
	float ScanRadius = 2000.f;
	
	UPROPERTY(EditAnywhere, Category = "Scan")
	float ScanInterval = 10.f;
	
	//Resource
	UPROPERTY(EditDefaultsOnly, Category = "Resource")
	TSubclassOf<AResourceNode> ResourceNodeClass;

	UPROPERTY(EditDefaultsOnly, Category = "Resource")
	EResourceType ResourceType;

	void AssignVillager(AVillager* Worker); // Assign the villager to work here
	void UnassignVillager(AVillager* Worker); // Unassign the villager from this building

protected:
	virtual void BeginPlay() override;

private:

	// Scan
	FTimerHandle ScanTimerHandle;

	TSet<FInstanceRef> ResourceInstancePool;
	TSet<TWeakObjectPtr<AVillager>> AssignedWorkers;
	
	TMap<TWeakObjectPtr<AVillager>, FInstanceRef> WorkerToResourceAssignments;
	TMap<FInstanceRef, TWeakObjectPtr<AVillager>> ResourceToWorkerAssignments;

	virtual void ScanArea(); // Scan an circular area to detect resources in range
	void RemoveResource(int InstanceIdx);
	
	void DistributeWork(AVillager* Worker); // Assign a resource to a given villager
	void RemoveWork(AVillager* Worker); // Remove the assigned resource from the given villager

};
