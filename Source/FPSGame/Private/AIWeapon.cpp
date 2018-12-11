// Fill out your copyright notice in the Description page of Project Settings.

#include "AIWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "FPSProjectile.h"


// Sets default values
AAIWeapon::AAIWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("WeaponMesh"));
	SetRootComponent(Mesh);

	MeleeMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("MeleeWeaponMesh"));
	MeleeMesh->SetupAttachment(Mesh);
	MeleeMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void AAIWeapon::Shoot()
{
	if (Ammo > 0)
	{
		AFPSProjectile* LastProjectile = GetWorld()->SpawnActor<AFPSProjectile>(Projectile, Mesh->GetSocketTransform(FName("Muzzle")));
		Ammo = Ammo - 1;
	}
}

void AAIWeapon::Reload()
{
	Ammo = MaxAmmo;
}

// Called when the game starts or when spawned
void AAIWeapon::BeginPlay()
{
	Super::BeginPlay();

	Ammo = MaxAmmo;
	
}

// Called every frame
void AAIWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

