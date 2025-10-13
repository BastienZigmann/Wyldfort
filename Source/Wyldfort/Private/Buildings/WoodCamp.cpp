// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/WoodCamp.h"

AWoodCamp::AWoodCamp()
    : ABaseBuilding()
{
    BuildingType = EBuildingType::Ressource;
    BuildingInteractionType = EBuildingInteractionType::Gather;
}