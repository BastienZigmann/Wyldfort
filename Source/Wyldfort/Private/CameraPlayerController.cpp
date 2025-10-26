// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "CameraPawn.h"
#include "Interface/MainHUDWidget.h"

ACameraPlayerController::ACameraPlayerController()
{
    //EnableDebug();

    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;
}

void ACameraPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Set up input mode safely after initialization
    FInputModeGameAndUI Mode;
    Mode.SetHideCursorDuringCapture(false);
    Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    SetInputMode(Mode);

    // Interface Initialization
    InitializeHUD();

    // Camera Controls
    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    if (!Subsystem) 
    {
        ErrorLog("EnhancedInputLocalPlayerSubsystem not found!", this);
        return;
    }
    if (InputMappingContext)
        Subsystem->AddMappingContext(InputMappingContext, 0);
    else
        WarningLog("InputMappingContext not set!", this);
    
    CameraPawn = Cast<ACameraPawn>(GetPawn());
    if (!CameraPawn)
    {
        ErrorLog("CameraPawn not found!", this);
        return;
    }
}

void ACameraPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
    if (!EnhancedInputComponent)
    {
        ErrorLog("EnhancedInputComponent not found!", this);
        return;
    }
    if (!MoveAction) WarningLog("MoveAction not set!", this);
    else EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACameraPlayerController::MoveCamera);
    if (!ZoomAction) WarningLog("ZoomAction not set!", this);
    else EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ACameraPlayerController::ZoomCamera);
    if (!RotateAction) WarningLog("RotateAction not set!", this);
    else EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &ACameraPlayerController::RotateCamera);
}

void ACameraPlayerController::PlayerTick(float DeltaTime)
{
    Super::PlayerTick(DeltaTime);
    HandleEdgeScroll();
}

void ACameraPlayerController::HandleEdgeScroll()
{
    if (!CameraPawn) return;
    float MouseX, MouseY;
    if (!GetMousePosition(MouseX, MouseY)) return;
    int32 ViewportX, ViewportY;
    GetViewportSize(ViewportX, ViewportY);
    int32 Threshold = CameraPawn->ScreenEdgeMoveThreshold;
    if (MouseX <= Threshold)
        CameraPawn->MoveCamera(-FVector::RightVector);
    else if (MouseX >= ViewportX - Threshold)
        CameraPawn->MoveCamera(FVector::RightVector);
    else if (MouseY <= Threshold)
        CameraPawn->MoveCamera(FVector::ForwardVector);
    else if (MouseY >= ViewportY - Threshold)
        CameraPawn->MoveCamera(-FVector::ForwardVector);
}

void ACameraPlayerController::MoveCamera(const FInputActionValue& Value)
{
    if (!CameraPawn) return;
    FVector Direction = FVector(Value.Get<FVector2D>().X, Value.Get<FVector2D>().Y, 0);
    CameraPawn->MoveCamera(Direction);
}

void ACameraPlayerController::ZoomCamera(const FInputActionValue& Value)
{
    DebugLog("ZoomCamera called");
    if (!CameraPawn) return;
    float ZoomValue = Value.Get<float>();
    CameraPawn->ZoomCamera(ZoomValue);
}
void ACameraPlayerController::RotateCamera(const FInputActionValue& Value)
{
    DebugLog("RotateCamera called");
    if (!CameraPawn) return;
    FVector2D RotateValue = Value.Get<FVector2D>();
    CameraPawn->RotateCamera(RotateValue.Y, RotateValue.X);
}

void ACameraPlayerController::InitializeHUD()
{
    if (!MainHUDWidgetClass)
    {
        WarningLog("MainHUDWidgetClass is not set, cannot initialize HUD.", this);
        return;
    }

    MainHUDWidgetInstance = CreateWidget<UMainHUDWidget>(this, MainHUDWidgetClass);
    if (MainHUDWidgetInstance)
    {
        MainHUDWidgetInstance->AddToViewport(0);
    }
}
