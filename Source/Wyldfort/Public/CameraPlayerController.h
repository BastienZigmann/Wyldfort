// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Core/Utils/Logger.h"
#include "CameraPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class WYLDFORT_API ACameraPlayerController : public APlayerController, public FLogger
{
	GENERATED_BODY()

public:
	ACameraPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<UInputMappingContext> InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<UInputAction> ZoomAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<UInputAction> RotateAction;

private:
	void HandleEdgeScroll();
	void MoveCamera(const FInputActionValue& Value);
	void ZoomCamera(const FInputActionValue& Value);
	void RotateCamera(const FInputActionValue& Value);

	TObjectPtr<class ACameraPawn> CameraPawn;

};
