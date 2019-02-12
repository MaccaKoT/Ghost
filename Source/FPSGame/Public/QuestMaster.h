// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestMaster.generated.h"

//Enums and Structs
UENUM(BlueprintType)
enum class E_QuestCategory : uint8
{
	MainQuest,
	SideQuest,
	Events
};

UENUM(BlueprintType)
enum class E_GoalTypes : uint8
{
	Custom,
	Hunt,
	Talk,
	Find
};

UENUM(BlueprintType)
enum class E_Regions : uint8
{
	SleepingCity,
	Dump,
	Wasteland,
	ForestWhite,
	SawmillZarya,
	Bar,
	NearMoscow
};

USTRUCT(BlueprintType)
struct F_Rewards
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Money;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Experience;
};

USTRUCT(BlueprintType)
struct F_GoalLocation
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool HasLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector Location;
};

USTRUCT(BlueprintType)
struct F_GoalInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool CustomGoal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		E_GoalTypes Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText AdditionalText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int AmountToHunt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		F_GoalLocation GoalLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool UpdateQuestDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText UpdatedDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<int> FollowingSubGoalIndices;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool UseRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLinearColor RadiusColor;
};

USTRUCT(BlueprintType)
struct F_QuestInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		E_QuestCategory Category;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		E_Regions Region;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		F_Rewards Rewards;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Difficulty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<F_GoalInfo> SubGoals;

};

//Main Class
UCLASS()
class FPSGAME_API AQuestMaster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuestMaster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestInfo")
		F_QuestInfo Quest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestInfo")
		TArray<int> StartingSubGoalIndices;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Not Edit")
		TArray<int> CurrentGoalIndices;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Not Edit")
		TArray<F_GoalInfo> CurrentGoals;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Not Edit")
		FText CurrentDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Not Edit")
		int CurrentHuntedAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Not Edit")
		int SelectedSubGoalIndex;

	UFUNCTION(BlueprintCallable, Category = "Quest")
		void UpdateSubGoals();

	UFUNCTION(BlueprintCallable, Category = "Quest")
		void SetupStartingGoals();

	UFUNCTION(BlueprintCallable, Category = "Quest")
		bool GoToNextSubGoal();

};

