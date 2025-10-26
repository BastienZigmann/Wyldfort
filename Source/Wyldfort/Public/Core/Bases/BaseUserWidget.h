// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Core/Utils/Logger.h"
#include "BaseUserWidget.generated.h"

UCLASS()
class WYLDFORT_API UBaseUserWidget : public UUserWidget, public FLogger
{
	GENERATED_BODY()
	
};
