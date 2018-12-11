// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSProjectile.h"
#include "AIWeapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	VE_Melee UMETA(DisplayName = "Melee"),
	VE_Shooting UMETA(DisplayName = "Shooting"),
};

UCLASS()
class FPSGAME_API AAIWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIWeapon();

	void Shoot();
	void Reload();

	int Ammo;

	bool isReloading;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		EWeaponType WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float ShootRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		TSubclassOf<AFPSProjectile> Projectile;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		UStaticMeshComponent* MeleeMesh;


	
};
