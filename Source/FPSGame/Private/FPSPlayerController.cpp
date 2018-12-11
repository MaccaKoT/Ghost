// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSPlayerController.h"
#include "FPSCharacter.h"



void AFPSPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateRotation(DeltaTime);
	

}

void AFPSPlayerController::UpdateRotation(float DeltaTime)
{
	/*if (!IsCameraInputEnabled())
		return;

	float Time = DeltaTime * (1 / GetActorTimeDilation());
	FRotator DeltaRot(0, 0, 0);

	DeltaRot.Yaw = GetPlayerCameraInput().X * (ViewYawSpeed * Time);
	DeltaRot.Pitch = GetPlayerCameraInput().Y * (ViewPitchSpeed * Time);
	DeltaRot.Roll = 0.0f;

	RotationInput = DeltaRot;*/

	Super::UpdateRotation(DeltaTime);
}



