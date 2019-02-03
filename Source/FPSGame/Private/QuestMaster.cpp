// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestMaster.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetArrayLibrary.h"

// Sets default values
AQuestMaster::AQuestMaster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AQuestMaster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AQuestMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AQuestMaster::UpdateSubGoals()
{
	CurrentGoals.Empty();

	for (int i = 0; i < CurrentGoalIndices.Num(); i++) 
	{
		int ActorInd = CurrentGoalIndices[i];
		F_GoalInfo Goal = Quest.SubGoals[ActorInd];
		
		CurrentGoals.Add(Goal);
	}

	return;
}

void AQuestMaster::SetupStartingGoals()
{
	CurrentGoalIndices.Empty();
	CurrentGoalIndices = StartingSubGoalIndices;
	CurrentDescription = Quest.Description;

	UpdateSubGoals();
}

bool AQuestMaster::GoToNextSubGoal()
{
	int MaxValue;
	int LastValueIndex;
	
	UKismetMathLibrary::MaxOfIntArray(CurrentGoalIndices, LastValueIndex, MaxValue);
	MaxValue = MaxValue + 1;

	Quest.SubGoals.Last(LastValueIndex);
	
	if (MaxValue <= LastValueIndex)
	{	
		CurrentGoalIndices.Empty();
		CurrentGoalIndices.Add(MaxValue);

		UpdateSubGoals();

		return true;
	}
	else
	{
		return false;
	}
}
