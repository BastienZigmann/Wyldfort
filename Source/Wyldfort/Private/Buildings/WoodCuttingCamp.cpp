#include "Buildings/WoodCuttingCamp.h"
#include "Resources/ResourceTypes.h"

AWoodCuttingCamp::AWoodCuttingCamp()
{
	ResourceType = EResourceType::Wood;

    EnableDebug();
    EnableDebugTraces();
}