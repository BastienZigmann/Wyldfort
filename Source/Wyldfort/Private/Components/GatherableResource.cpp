// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GatherableResource.h"
#include "Misc/Guid.h"
#include "UObject/Package.h"

UGatherableResource::UGatherableResource()
{
}

void UGatherableResource::OnRegister()
{
    Super::OnRegister();

    if (!ComponentGuid.IsValid())
    {
        ComponentGuid = FGuid::NewGuid();

#if WITH_EDITOR
        // Mark package dirty so the GUID is serialized into the level/asset in editor.
        if (GetOuter())
        {
            // In editor, marking the outer package dirty helps persist the new GUID.
            GetOuter()->MarkPackageDirty();
        }
#endif

    }
}

#if WITH_EDITOR
void UGatherableResource::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);
    // Keep GUID valid when editing in the editor
    if (!ComponentGuid.IsValid())
    {
        ComponentGuid = FGuid::NewGuid();
        if (GetOuter())
        {
            GetOuter()->MarkPackageDirty();
        }
    }
}
#endif