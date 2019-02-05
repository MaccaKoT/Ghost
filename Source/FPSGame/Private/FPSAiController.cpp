// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAiController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "AIWeapon.h"
#include "AICharacter.h"


AFPSAiController::AFPSAiController()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AFPSAiController::BeginPlay()
{
	Super::BeginPlay();

	AiCharacter = Cast<AAICharacter>(GetPawn());
	
	NextPoint = true;
	isPatrolling = true;
	isAttack = false;
	isSearching = false;

	GetWorldTimerManager().SetTimer(BeginPlayTimer, this, &AFPSAiController::StartAiPatrol, 1.0f, true);

	
}

void AFPSAiController::StartAiPatrol()
{
	if (AiCharacter->isDead == true)
	{
		return;
	}
	if (isPatrolling == false)
	{
		GetWorldTimerManager().ClearTimer(BeginPlayTimer);
	}

	StartPatrol();
}

void AFPSAiController::SearchPlayer()
{
	if (AiCharacter->isDead || isPatrolling || AiCharacter->isEQS)
	{
		return;
	}

	if (AiCharacter->isHaveWeapon == false || AiCharacter->Weapon->WeaponType == EWeaponType::VE_Melee)
	{
		if (AiStimulus)
		{
			isSearching = false;
			MoveToActor(MainTarget);
		}

		else
		{
			isSearching = true;
			MoveToLocation(MainTarget->GetActorLocation());
		}

		return;
	}
	if (AiCharacter->isHaveWeapon && AiCharacter->Weapon->WeaponType == EWeaponType::VE_Shooting)
	{
		StopMovement();

		if (AiStimulus)
		{
			isSearching = false;
			AiCharacter->isAiming = true;

			GetWorldTimerManager().SetTimer(ShootTimer, AiCharacter, &AAICharacter::FireInPlayer, AiCharacter->Weapon->ShootRate, false);
		}

		else
		{
			AiCharacter->isAiming = false;
			isSearching = true;

		}

		return;
	}
}

void AFPSAiController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult & Result)
{
	if (Result.IsSuccess() && isPatrolling && isSearching == false)
	{
		NextPoint = true;
		AiCharacter->isAiming = false;

		return;
	}

	if (Result.IsSuccess() && MainTarget != nullptr && isPatrolling == false && isAttack == false && isSearching == false)
	{
		isAttack = true;

		AiCharacter->MeleeAttack();
		
		StopMovement();
		GetWorldTimerManager().ClearTimer(SearchPlayerTimer);

		return;
	}

	if (isSearching)
	{
		isPatrolling = true;
		NextPoint = true;
		
		GetWorldTimerManager().SetTimer(BeginPlayTimer, this, &AFPSAiController::StartAiPatrol, 1.0f, true);
	}
}

void AFPSAiController::AiPatrol()
{
	if (AiCharacter->RandomPatrol)
	{
		RandomPatrol();
	}
	else
	{
		TArray<ATargetPoint*> Points = AiCharacter->Points;

		if (Points.Num() <= 0)
		{
			return;
		}

		int PointIndex = FMath::RandRange(0, Points.Num() - 1);
		ATargetPoint* PointTarget = Points[PointIndex];

		if (PointTarget == LastPoint)
		{
			return;
		}

		FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(AiCharacter->GetActorLocation(), PointTarget->GetActorLocation());
		FVector LookVector = LookRotation.Vector();
		FVector LookPointVector = FVector(0.0f, 0.0f, LookVector.Z);

		AiCharacter->AddActorWorldOffset(LookPointVector,true);
		
		MoveToLocation(PointTarget->GetActorLocation());
		NextPoint = false;

		LastPoint = PointTarget;
	}
}

void AFPSAiController::PerceprionUpdate(AActor * Actor, bool SuccessStimulus)
{
	if (AiCharacter->isDead)
	{
		return;
	}

	if (AiCharacter->AiState == EAiStateEnum::VE_Friendly)
	{
		if (isPlayerEnemy)
		{
			HideFromPlayer();
		}

		return;
	}

	AFPSCharacter* PlayerTarget = Cast<AFPSCharacter>(Actor);
	AAICharacter* AiTarget = Cast<AAICharacter>(Actor);

	if ((PlayerTarget != nullptr && (isPlayerEnemy || AiCharacter->AiState == EAiStateEnum::VE_Enemy)) || (AiTarget != nullptr && ((AiTarget->GroupIndex != AiCharacter->GroupIndex && AiCharacter->AiState == EAiStateEnum::VE_Enemy) || (AiTarget->AiState == EAiStateEnum::VE_Enemy && AiTarget->GroupIndex != AiCharacter->GroupIndex))))
	{
		isSearching = false;

		ACharacter* Target = Cast<ACharacter>(Actor);

		GetWorldTimerManager().SetTimer(SearchPlayerTimer, this, &AFPSAiController::SearchPlayer, 0.01f, true);
		
		AiStimulus = SuccessStimulus;
		isPatrolling = false;

		MainTarget = Target;

		AiCharacter->isEQS = false;
	}
}

FTimerHandle AFPSAiController::SetSearchTimer()
{
	GetWorldTimerManager().SetTimer(SearchPlayerTimer, this, &AFPSAiController::SearchPlayer, 0.01f, true);
	
	return SearchPlayerTimer;
}

void AFPSAiController::ClearTarget()
{
	MainTarget = nullptr;
	isPatrolling = true;
	NextPoint = true;

	GetWorldTimerManager().SetTimer(BeginPlayTimer, this, &AFPSAiController::StartAiPatrol, 1.0f, true);
}
