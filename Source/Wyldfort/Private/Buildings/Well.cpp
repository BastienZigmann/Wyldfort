// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/Well.h"

AWell::AWell()
    : ABaseBuilding()
{
    BuildingType = EBuildingType::Well;
    BuildingInteractionType = EBuildingInteractionType::Wait;
}