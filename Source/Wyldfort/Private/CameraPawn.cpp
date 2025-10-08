// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ACameraPawn::ACameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//EnableDebug();

	CurrentZoom = DefaultZoom;

}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
	SpringArm = FindComponentByClass<USpringArmComponent>();
	if (!SpringArm) 
	{
		ErrorLog("SpringArm component not found!", this);
		return;
	}
	SpringArm->TargetArmLength = CurrentZoom;
	Camera = FindComponentByClass<UCameraComponent>();
	if (!Camera)
	{
		ErrorLog("Camera component not found!", this);
		return;
	}

}

void ACameraPawn::ZoomCamera(float Value)
{
	DebugLog("ZoomCamera called");
	if (!SpringArm) return;
	CurrentZoom = FMath::Clamp(CurrentZoom - Value * ZoomSpeed, MinZoom, MaxZoom);
	SpringArm->TargetArmLength = CurrentZoom;
}

void ACameraPawn::MoveCamera(FVector Direction, float Value)
{
	if (Direction.IsNearlyZero() || FMath::IsNearlyZero(Value)) return;

    // Interpret Direction in pawn local space and convert to world
    FVector WorldDir = GetActorRotation().RotateVector(Direction);
    WorldDir.Z = 0.f;                    // stay on ground plane
    WorldDir = WorldDir.GetSafeNormal(); // handle diagonals consistently

    const float DT = GetWorld() ? GetWorld()->GetDeltaSeconds() : 0.f;
    const FVector Delta = WorldDir * MoveSpeed * Value * DT;
	DebugLog("MoveCamera called: " + Delta.ToString());

    AddActorWorldOffset(Delta, /*bSweep=*/true);
}

void ACameraPawn::RotateCamera(float Pitch, float Yaw)
{
	DebugLog("RotateCamera called");
	if (!SpringArm) return;
    const float DT = (GetWorld() ? GetWorld()->GetDeltaSeconds() : 0.f);
    if (DT <= 0.f) return;

    // Yaw: rotate the whole pawn so forward/right match the view
    if (!FMath::IsNearlyZero(Yaw))
    {
        const float DeltaYaw = Yaw * RotateSpeed * DT; // degrees
        AddActorWorldRotation(FRotator(0.f, DeltaYaw, 0.f));
    }
}