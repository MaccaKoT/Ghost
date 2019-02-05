// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.h"
#include "AIWeapon.h"
#include "FPSAiController.h"
#include "Engine/TargetPoint.h"
#include "Components/BoxComponent.h"
#include "AICharacter.generated.h"

UENUM(BlueprintType)
enum class EAiStateEnum : uint8
{
	VE_Friendly UMETA(DisplayName = "Friendly"),
	VE_Neutral  UMETA(DisplayName = "Neutral"),
	VE_Enemy    UMETA(DisplayName = "Enemy"),
	VE_Mutant   UMETA(DisplayName = "Mutant"),
};

UCLASS()
class FPSGAME_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacter();

	AFPSCharacter* Player;
	AFPSAiController* AiController;
	AAIWeapon* Weapon;
	FTimerHandle ShootTimer;

	bool PlayerIsEnemy;
	bool isHaveWeapon;

	void FireInPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
		UBoxComponent* WeaponLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		TSubclassOf<AAIWeapon> WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		EAiStateEnum AiState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		TArray<ATargetPoint*> Points;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		bool RandomPatrol;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 GroupIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Not Edit")
		bool isDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Not Edit")
		bool isSeen;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Not Edit")
		bool isEQS;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Not Edit")
	    bool isAiming;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Not Edit")
		float Health;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Not Edit")
	    float Pitch;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Perception")
		UAIPerceptionComponent* AIPerception;

	UFUNCTION(BlueprintCallable)
		void Death();

	UFUNCTION(BlueprintImplementableEvent)
		void MeleeAttack();

	UFUNCTION(BlueprintImplementableEvent)
		void Interact();

	
};
