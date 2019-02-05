// Fill out your copyright notice in the Description page of Project Settings.

#include "AICharacter.h"
#include "Engine/World.h"
#include "FPSCharacter.h"
#include "TimerManager.h"
#include "AIWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponLocation = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponLocation"));
	WeaponLocation->SetupAttachment(GetMesh(),FName("Weapon"));
	
}


void AAICharacter::FireInPlayer()
{
	if (isHaveWeapon && Weapon->WeaponType == EWeaponType::VE_Shooting && Weapon->isReloading == false)
	{
		if (Weapon->Ammo <= 0)
		{
			return;
		}
		else
		{
			Weapon->Shoot();
		}
	}
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	AiController = Cast<AFPSAiController>(GetController());
	
	if (WeaponClass != nullptr)
	{
		FActorSpawnParameters WeaponSP;
		WeaponSP.Owner = this;
		
		Weapon = GetWorld()->SpawnActor<AAIWeapon>(WeaponClass,WeaponSP);
		Weapon->AttachToActor(this,FAttachmentTransformRules::KeepRelativeTransform);
		Weapon->AttachToComponent(WeaponLocation,FAttachmentTransformRules::KeepRelativeTransform);
		
		isHaveWeapon = true;
	}
	else
	{
		isHaveWeapon = false;
	}

	Health = MaxHealth + FMath::RandRange(-50.f, 50.f);

	if (Health <= 0)
	{
		Health = FMath::RandRange(50.f, 100.f);
	}

	isDead = false;	
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAICharacter::Death()
{
	isDead = true;

	GetCapsuleComponent()->DestroyComponent();
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	if (isHaveWeapon)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		if (Weapon->Mesh != nullptr)
		{
			Weapon->Mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
			Weapon->Mesh->SetSimulatePhysics(true);
		}
		if(Weapon->MeleeMesh != nullptr)
		{
			Weapon->MeleeMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
			Weapon->MeleeMesh->SetSimulatePhysics(true);
		}
	}
	
	AiController->StopMovement();
}









