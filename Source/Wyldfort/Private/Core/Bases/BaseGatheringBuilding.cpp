#include "Core/Bases/BaseGatheringBuilding.h"
#include "Characters/Villager.h"
#include "Resources/GatherableFoliage.h"
#include "Resources/ResourceNode.h"
#include "Engine/OverlapResult.h"

ABaseGatheringBuilding::ABaseGatheringBuilding()
{
    BuildingType = EBuildingType::ResourceGathering;
    BuildingInteractionType = EBuildingInteractionType::Gather;
}

void ABaseGatheringBuilding::BeginPlay() 
{
    Super::BeginPlay();

	ScanArea();

	if (ScanInterval > 0.f && GetWorld())
	{
		GetWorldTimerManager().SetTimer(ScanTimerHandle, this, &ABaseGatheringBuilding::ScanArea, ScanInterval, true);
	}
}

void ABaseGatheringBuilding::AssignVillager(AVillager* Worker)
{
	if (!Worker)
	{
		WarningLog(FString::Printf(TEXT("Attempted to assign null villager to %s"), *GetName()), this);
		return;
	}

	if (AssignedWorkers.Contains(Worker))
	{
		WarningLog(FString::Printf(TEXT("Villager already assigned to this %s"), *GetName()), this);
		return;
	}

	AssignedWorkers.Add(Worker);
	Worker->SetWorkBuilding(this);
	DistributeWork(Worker);
	DebugLog(FString::Printf(TEXT("Villager assigned to %s"), *GetName()), this);
}

void ABaseGatheringBuilding::UnassignVillager(AVillager* Worker)
{
	if (!Worker)
	{
		WarningLog(FString::Printf(TEXT("Attempted to unassign null villager from %s"), *GetName()), this);
		return;
	}

	if (!AssignedWorkers.Contains(Worker))
	{
		WarningLog(FString::Printf(TEXT("Villager not assigned to this %s"), *GetName()), this);
		return;
	}

	AssignedWorkers.Remove(Worker);
	Worker->SetWorkBuilding(nullptr);
	RemoveWork(Worker);
	DebugLog(FString::Printf(TEXT("Villager unassigned from %s"), *GetName()), this);
}

void ABaseGatheringBuilding::DistributeWork(AVillager* Worker)
{
	if (!Worker) return;
	if (!AssignedWorkers.Contains(Worker)) return; // If worker doesn't work here
	if (WorkerToResourceAssignments.Contains(Worker)) return; // Already a resource assigned
	
	// Find an unassigned resource from the pool
	for (const FInstanceRef& ResourceRef : ResourceInstancePool)
	{
		if (ResourceToWorkerAssignments.Contains(ResourceRef)) continue; // Already assigned to someone else

		// Assign this resource to the worker
		WorkerToResourceAssignments.Add(Worker, ResourceRef);
		ResourceToWorkerAssignments.Add(ResourceRef, Worker);

		DebugLog(FString::Printf(TEXT("Assigned resource instance %d to worker %s"), ResourceRef.InstanceIndex, *Worker->GetName()), this);
		break;
	}

}

void ABaseGatheringBuilding::RemoveWork(AVillager* Worker)
{
	if (!Worker) return;
	if (!WorkerToResourceAssignments.Contains(Worker)) return; // If the worker isn't assigned any resource, do nothing

	FInstanceRef resource = WorkerToResourceAssignments.FindRef(Worker);

	WorkerToResourceAssignments.Remove(Worker);
	ResourceToWorkerAssignments.Remove(resource);

	DebugLog(FString::Printf(TEXT("Removed assigned resource instance %d from worker %s"), resource.InstanceIndex, *Worker->GetName()), this);

}


void ABaseGatheringBuilding::ScanArea()
{
    if (!GetWorld()) return;
	if (ResourceInstancePool.Num() >= AssignedWorkers.Num() * 2) return; // Fixed: should be >= not <

	const FVector Origin = GetActorLocation();
	const float RadiusSqr = ScanRadius * ScanRadius;

	// Prepare overlap query
	TArray<FOverlapResult> Overlaps;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(GatheringBuildingScan), /*bTraceComplex=*/false);
	QueryParams.AddIgnoredActor(this);

	// Sphere overlap 
	const bool bAny = GetWorld()->OverlapMultiByObjectType(
		Overlaps,
		Origin,
		FQuat::Identity,
		ObjectQueryParams,
		FCollisionShape::MakeSphere(ScanRadius),
		QueryParams
	);

	// Collect found instances with distance for sorting
	struct FPair { float DistSqr; FInstanceRef InstanceRef; };
	TArray<FPair> Found;
	Found.Reserve(64);

	if (bAny)
	{
		// Track which components we've already processed to avoid duplicate work
		TSet<UGatherableFoliage*> ProcessedComponents;
		ProcessedComponents.Reserve(32);

		for (const FOverlapResult& R : Overlaps)
		{
			UPrimitiveComponent* Prim = R.GetComponent();
			if (!Prim) continue;

			// Only consider our custom gatherable foliage component type
			if (UGatherableFoliage* GatherComp = Cast<UGatherableFoliage>(Prim))
			{
				// Skip if we've already processed this component
				if (ProcessedComponents.Contains(GatherComp)) continue;
				
				if (GatherComp->ResourceType != ResourceType) continue;
				
				DebugLog(" Processing component: " + Prim->GetName(), this);
				// Mark this component as processed
				ProcessedComponents.Add(GatherComp);

				const int32 Count = GatherComp->GetInstanceCount();
				for (int32 InstanceIdx = 0; InstanceIdx < Count; ++InstanceIdx)
				{
					FTransform InstanceTransform;
					if (!GatherComp->GetInstanceTransform(InstanceIdx, InstanceTransform, /*bWorldSpace=*/true)) continue;

					const float D2 = FVector::DistSquared(Origin, InstanceTransform.GetLocation());
					if (D2 > RadiusSqr) continue; // instance might be outside even if component bounds overlap

					// Create instance reference
					FInstanceRef InstanceRef;
					InstanceRef.InstanceIndex = InstanceIdx;
					InstanceRef.ComponentGuid = GatherComp->ComponentGuid;
					InstanceRef.Location = InstanceTransform.GetLocation();
					InstanceRef.NeedUpdateIfRemoval = (InstanceIdx == Count - 1); // Last instance needs update if removed
					InstanceRef.Node = nullptr; // Will be set when resource is assigned to worker

					// Skip if already in resource pool
					if (ResourceInstancePool.Contains(InstanceRef)) continue;

					Found.Add({ D2, InstanceRef });
				}
			}
		}
	}

	// If overlap returned nothing, stop updating
	if (Found.Num() == 0)
	{
		const float DebugDuration = 10.f;
		const int32 Segments = 48;
		DrawDebugCircle(GetWorld(), Origin, ScanRadius, Segments, FColor::Yellow, false, DebugDuration, 0, 3.f, FVector::ForwardVector, FVector::RightVector, true);
		DebugLog("No new resources found in scan area", this);

		// If we didn't find any new resources, we can stop updating
		GetWorld()->GetTimerManager().ClearTimer(ScanTimerHandle);
		ResourceInstancePool.Empty();
		
		return;
	}

	// Sort by distance and add closest resources to pool
	Found.Sort([](const FPair& A, const FPair& B) { return A.DistSqr < B.DistSqr; });
	
	int32 Added = 0;
	const int32 MaxToAdd = (AssignedWorkers.Num() * 2) - ResourceInstancePool.Num();
	for (int32 i = 0; i < Found.Num() && Added < MaxToAdd; ++i)
	{
		ResourceInstancePool.Add(Found[i].InstanceRef);
		Added++;
	}

	DebugLog(FString::Printf(TEXT("Added %d resources to pool (total: %d)"), Added, ResourceInstancePool.Num()), this);

	// Debug visuals
	const float DebugDuration = 10.f;
	const int32 Segments = 48;
	DrawDebugCircle(GetWorld(), Origin, ScanRadius, Segments, FColor::Green, false, DebugDuration, 0, 3.f, FVector::ForwardVector, FVector::RightVector, false);

	const int32 VisualizeCount = FMath::Min<int32>(10, Added);
	for (int32 i = 0; i < VisualizeCount; ++i)
	{
		const FVector& Loc = Found[i].InstanceRef.Location;
		DebugLog(FString::Printf(TEXT("  Resource %d at distance %.1f"), i, FMath::Sqrt(Found[i].DistSqr)), this);
		DrawDebugLine(GetWorld(), Origin, Loc, FColor::Green, false, DebugDuration, 0, 2.f);
		DrawDebugSphere(GetWorld(), Loc, 16.f, 8, FColor::Cyan, false, DebugDuration, 0, 1.f);
	}
}

void ABaseGatheringBuilding::RemoveResource(int InstanceIdx)
{
	// Find the resource in our pool
	FInstanceRef* FoundRef = nullptr;
	for (FInstanceRef& Ref : ResourceInstancePool)
	{
		if (Ref.InstanceIndex == InstanceIdx)
		{
			FoundRef = &Ref;
			break;
		}
	}

	if (!FoundRef)
	{
		WarningLog(FString::Printf(TEXT("Resource instance %d not found in pool"), InstanceIdx), this);
		return;
	}

	// Find the component to remove the instance from
	UGatherableFoliage* GatherComp = nullptr;
	for (TObjectIterator<UGatherableFoliage> It; It; ++It)
	{
		if (It->GetWorld() == GetWorld() && It->ComponentGuid == FoundRef->ComponentGuid)
		{
			GatherComp = *It;
			break;
		}
	}

	if (!GatherComp)
	{
		ErrorLog(FString::Printf(TEXT("Component with GUID not found for resource instance %d"), InstanceIdx), this);
		ResourceInstancePool.Remove(*FoundRef);
		return;
	}

	const int32 TotalInstances = GatherComp->GetInstanceCount();
	if (InstanceIdx < 0 || InstanceIdx >= TotalInstances)
	{
		ErrorLog(FString::Printf(TEXT("Invalid instance index %d (total: %d)"), InstanceIdx, TotalInstances), this);
		ResourceInstancePool.Remove(*FoundRef);
		return;
	}

	// Remove the foliage instance
	const bool bSuccess = GatherComp->RemoveInstance(InstanceIdx);
	if (!bSuccess)
	{
		ErrorLog(FString::Printf(TEXT("Failed to remove resource instance %d from component"), InstanceIdx), this);
		ResourceInstancePool.Remove(*FoundRef);
		return;
	}

	DebugLog(FString::Printf(TEXT("Removed resource instance %d from foliage component"), InstanceIdx), this);

	// Remove from pool
	ResourceInstancePool.Remove(*FoundRef);

	// Update indices: When an instance is removed, the last instance moves to fill its spot
	// So if we removed something other than the last instance, we need to update the reference
	// that pointed to the last instance
	if (FoundRef->NeedUpdateIfRemoval)
	{
		// We removed the last instance, no index updates needed
		DebugLog("Removed last instance, no index updates needed", this);
	}
	else
	{
		// We removed a middle instance, so the last instance moved to this index
		// Find and update the reference that pointed to the last instance
		const int32 LastInstanceIdx = TotalInstances - 1; // Before removal
		
		for (FInstanceRef& Ref : ResourceInstancePool)
		{
			if (Ref.ComponentGuid == FoundRef->ComponentGuid && Ref.InstanceIndex == LastInstanceIdx)
			{
				// This reference pointed to the last instance, which is now at the removed index
				FInstanceRef UpdatedRef = Ref;
				UpdatedRef.InstanceIndex = InstanceIdx;
				UpdatedRef.NeedUpdateIfRemoval = false; // It's no longer the last instance
				
				ResourceInstancePool.Remove(Ref);
				ResourceInstancePool.Add(UpdatedRef);
				
				DebugLog(FString::Printf(TEXT("Updated instance index from %d to %d"), LastInstanceIdx, InstanceIdx), this);
				break;
			}
		}
	}

	DebugLog(FString::Printf(TEXT("Resource pool updated (total: %d)"), ResourceInstancePool.Num()), this);
}