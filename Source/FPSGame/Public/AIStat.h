// Fill out your copyright notice in the Description page of Project Settings.

#include "AIStat.generated.h"

UENUM(BlueprintType)
enum AiStat
{
	Enemy UMETA(DisplayName = "Enemy"),
	Neutral UMETA(DisplayName = "Neutral"),
	Friendly UMETA(DisplayName = "Friendly"),
	MutantEnemy UMETA(DisplayName = "MutantEnemy"),
};