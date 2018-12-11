// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "FPSCharacter.generated.h"

class AFPSProjectile;

UCLASS()
class AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFPSCharacter();

	virtual void BeginPlay() override;

protected:

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	/* Movement functions */
	void MoveForward(float Val);
	void MoveRight(float Val);

	void Turn(float Val);
	void LookUp(float Val);

	void Fire();
	void Hit();

	void StopAim();
	void StartAim();

	void ReloadStart();
	void ReloadStop();

	void StartSprint();
	void StopSprint();

	bool bIsReloading;

public:

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
		UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		USkeletalMeshComponent* Arms;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		USkeletalMeshComponent* Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		USkeletalMeshComponent* Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		USkeletalMeshComponent* BodyWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		TSubclassOf<AFPSProjectile> Projectile;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool bIsCarryingObjective;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool bIsAiming;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay")
		float YawInput;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay")
		float PitchInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay")
		float Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool Sprint = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		float ReloadTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		float MaxHealth;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool bIsKicking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool isDead;

	UFUNCTION()
		void StartingCrouch();

	UFUNCTION(BlueprintImplementableEvent)
		void Tackle();

	UFUNCTION(BlueprintImplementableEvent)
		void Kick();

	UFUNCTION(BlueprintImplementableEvent)
		void Reload();

	UFUNCTION(BlueprintImplementableEvent)
		void ShootAnim();

	UFUNCTION(BlueprintImplementableEvent)
		void AimingAnim(bool Aim);
	



};