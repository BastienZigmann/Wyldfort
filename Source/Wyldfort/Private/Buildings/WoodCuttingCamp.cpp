#include "Buildings/WoodCuttingCamp.h"
#include "Core/Types/ResourceTypes.h"

AWoodCuttingCamp::AWoodCuttingCamp()
{
	ResourceType = EResourceType::Wood;

    EnableDebug();
    EnableDebugTraces();
}