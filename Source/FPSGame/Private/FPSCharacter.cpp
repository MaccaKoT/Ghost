// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSCharacter.h"
#include "FPSProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h"
#include "TimerManager.h"


AFPSCharacter::AFPSCharacter()
{
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	Camera->SetupAttachment(GetMesh(), TEXT("head"));
	Camera->bUsePawnControlRotation = true;

	Arms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arms"));
	Arms->SetupAttachment(Camera);
	Arms->bOnlyOwnerSee = true;
	Arms->CastShadow = false;
	
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(Arms,FName("Weapon"));
	Weapon->bOnlyOwnerSee = true;
	Weapon->CastShadow = false;

	Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(GetMesh());
	Body->bOwnerNoSee = true;
	Body->CastShadow = true;
	Body->bCastHiddenShadow = true;

	BodyWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BodyWeapon"));
	BodyWeapon->SetupAttachment(Body,FName("Weapon"));
	BodyWeapon->bOwnerNoSee = true;
	BodyWeapon->CastShadow = true;
	BodyWeapon->bCastHiddenShadow = true;

}


void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
}

void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);
	
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AFPSCharacter::ReloadStart);
	PlayerInputComponent->BindAction("Hit", IE_Pressed, this, &AFPSCharacter::Hit);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AFPSCharacter::StartingCrouch);

	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AFPSCharacter::StartAim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AFPSCharacter::StopAim);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AFPSCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AFPSCharacter::StopSprint);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::LookUp);
}

void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPSCharacter::Fire()
{
	if (bIsReloading == true || bIsKicking == true)
	{
		return;
	}

	if (Sprint == true)
	{
		StopSprint();
		return;
	}
	
	AFPSProjectile* LastProjectile;
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.Instigator = this;

	FVector SocketLocation = Weapon->GetSocketLocation(FName("Muzzle"));
	FRotator SocketRotation = Weapon->GetSocketRotation(FName("Muzzle"));

	LastProjectile = GetWorld()->SpawnActor<AFPSProjectile>(Projectile, SocketLocation, SocketRotation, SpawnParameters);

	ShootAnim();
}

void AFPSCharacter::Hit()
{
	if (bIsCrouched == false && bIsReloading == false && bIsKicking == false)
	{
		if (bIsAiming == true)
		{
			StopAim();
		}
		if (Sprint == true)
		{
			StopSprint();
		}
		
		bIsKicking = true;
		Kick();
	}
}

void AFPSCharacter::StartAim()
{
	if (bIsReloading == true || bIsKicking == true)
	{
		return;
	}
	if (Sprint == true)
	{
		StopSprint();
		return;
	}

	AimingAnim(true);
	
	Camera->SetFieldOfView(70.f);
	bIsAiming = true;
}

void AFPSCharacter::StopAim()
{
	AimingAnim(false);
	Camera->SetFieldOfView(90.f);
	bIsAiming = false;
}

void AFPSCharacter::ReloadStop()
{
	bIsReloading = false;
}

void AFPSCharacter::StartSprint()
{
	if ((Sprint == false))
	{
		if (bIsCrouched == true)
		{
			UnCrouch();
		}
		if (bIsAiming == true)
		{
			StopAim();
		}
		Sprint = true;

		GetCharacterMovement()->MaxWalkSpeed = 800.f;
	}
	else
	{
		StopSprint();
	}
}

void AFPSCharacter::StopSprint()
{
	if (Sprint == true)
	{
		Sprint = false;

		GetCharacterMovement()->MaxWalkSpeed = 450.f;
	}
}

void AFPSCharacter::ReloadStart()
{
	if (bIsReloading != true)
	{
		bIsReloading = true;
		FTimerHandle ReloadTimer;
		
		GetWorldTimerManager().SetTimer(ReloadTimer, this, &AFPSCharacter::ReloadStop, ReloadTime, false);

		Reload();
	}
}

void AFPSCharacter::StartingCrouch()
{
	if (bIsCrouched == false)
	{
		Crouch();
		if (Sprint == true)
		{
			StopSprint();
			Tackle();
		}
	}
	else
	{
		UnCrouch();
	}
}

void AFPSCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}

	if (Value <= 0)
	{
		StopSprint();
	}
}

void AFPSCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AFPSCharacter::Turn(float Val)
{
	AddControllerYawInput(Val);
	YawInput = Val;
}

void AFPSCharacter::LookUp(float Val)
{
	AddControllerPitchInput(Val);
	PitchInput = Val;
}

