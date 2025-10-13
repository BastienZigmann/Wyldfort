// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/SawMill.h"

ASawMill::ASawMill()
    : ABaseBuilding()
{
    BuildingType = EBuildingType::Industry;
    BuildingInteractionType = EBuildingInteractionType::Enter;
}