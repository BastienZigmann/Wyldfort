// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Core/Utils/Logger.h"
#include "CameraPawn.generated.h"

UCLASS()
class WYLDFORT_API ACameraPawn : public APawn, public FLogger
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraPawn();

	void ZoomCamera(float Value);
	void MoveCamera(FVector Direction, float Value = 1.0f);
	void RotateCamera(float Pitch, float Yaw);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MoveSpeed = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	int32 ScreenEdgeMoveThreshold = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float RotateSpeed = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float ZoomSpeed = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MinZoom = 300.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MaxZoom = 3000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float DefaultZoom = 1000.0f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:

	TObjectPtr<class USpringArmComponent> SpringArm;
	TObjectPtr<class UCameraComponent> Camera;

	float CurrentZoom = 1000.0f;

};
