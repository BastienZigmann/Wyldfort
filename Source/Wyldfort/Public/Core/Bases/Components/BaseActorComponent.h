// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/Utils/Logger.h"
#include "BaseActorComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WYLDFORT_API UBaseActorComponent : public UActorComponent, public FLogger
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	template<typename T>
	T* GetOwnerComponent() const
	{
		return GetOwner() ? GetOwner()->FindComponentByClass<T>() : nullptr;
	}

	template<typename T>
	T* GetOwnerTyped() const
	{
		return Cast<T>(GetOwner());
	}


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
