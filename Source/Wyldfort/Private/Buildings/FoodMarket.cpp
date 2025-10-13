// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/FoodMarket.h"

AFoodMarket::AFoodMarket()
    : ABaseBuilding()
{
    BuildingType = EBuildingType::FoodMarket;
    BuildingInteractionType = EBuildingInteractionType::Wait;
}