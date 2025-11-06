// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GatherableRessource.h"
#include "Misc/Guid.h"
#include "UObject/Package.h"

UGatherableRessource::UGatherableRessource()
{
}

void UGatherableRessource::OnRegister()
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
void UGatherableRessource::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
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