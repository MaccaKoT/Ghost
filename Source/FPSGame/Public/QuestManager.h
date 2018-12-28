// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Runtime/UMG/Public/UMG.h"
#include "QuestMaster.h"
#include "QuestManager.generated.h"

UCLASS()
class FPSGAME_API AQuestManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuestManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, Category = "Default", meta = (ExposeOnSpawn = "true"))
		ACharacter* Character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		AQuestMaster* CurrentQuest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		F_GoalInfo CurrentGoal;

	UFUNCTION(BlueprintCallable)
		void OnSwitchQuest();

};
