// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Engine/TargetPoint.h"
#include "Perception/AIPerceptionComponent.h"
#include "FPSAiController.generated.h"

class AAICharacter;
class AFPSCharacter;

UCLASS()
class FPSGAME_API AFPSAiController : public AAIController
{
	GENERATED_BODY()

public:

	AFPSAiController();

	virtual void BeginPlay() override;

	AAICharacter* AiCharacter;
	ATargetPoint* LastPoint;

	bool AiStimulus;
	bool isSearching;
	
	FTimerHandle BeginPlayTimer;
	FTimerHandle SearchPlayerTimer;
	FTimerHandle ShootTimer;

	void StartAiPatrol();
	void SearchPlayer();
	
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult & Result) override;

public:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "NotEdit")
		ACharacter* MainTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "NotEdit")
		bool NextPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "NotEdit")
		bool isPatrolling;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "NotEdit")
		bool isPlayerEnemy;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "NotEdit")
		bool isAttack;

	UFUNCTION(BlueprintCallable)
		void PerceprionUpdate(AActor * Actor, bool SuccessStimulus);

	UFUNCTION(BlueprintCallable)
		FTimerHandle SetSearchTimer();

	UFUNCTION(BlueprintCallable)
		void ClearTarget();

	UFUNCTION(BlueprintCallable)
		void AiPatrol();

	UFUNCTION(BlueprintImplementableEvent)
		void StartPatrol();

	UFUNCTION(BlueprintImplementableEvent)
		void RandomPatrol();

	UFUNCTION(BlueprintImplementableEvent)
		void HideFromPlayer();
};
