// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Core/Utils/Logger.h"
#include "CameraPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UMainHUDWidget;

UCLASS()
class WYLDFORT_API ACameraPlayerController : public APlayerController, public FLogger
{
	GENERATED_BODY()

public:
	ACameraPlayerController();

	// Controls
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<UInputMappingContext> InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<UInputAction> ZoomAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<UInputAction> RotateAction;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;

	// HUD
	UPROPERTY(EditDefaultsOnly, Category = "HUD")
	TSubclassOf<UMainHUDWidget> MainHUDWidgetClass;
	UPROPERTY(Transient)
	TObjectPtr<UMainHUDWidget> MainHUDWidgetInstance;

private:
	// Controls handling
	void HandleEdgeScroll();
	void MoveCamera(const FInputActionValue& Value);
	void ZoomCamera(const FInputActionValue& Value);
	void RotateCamera(const FInputActionValue& Value);

	TObjectPtr<class ACameraPawn> CameraPawn;

	// HUD
	void InitializeHUD();

};
