// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractiveActor.h"
#include "FPSCharacter.h"

// Sets default values
AInteractiveActor::AInteractiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractiveActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractiveActor::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
}

void AInteractiveActor::Interact()
{
	UE_LOG(LogTemp,Log,TEXT("Interact"))
}

// Called every frame
void AInteractiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractiveActor::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AFPSCharacter* Player = Cast<AFPSCharacter>(OtherActor);

	if (Player != nullptr)
	{
		Player->InteractActor = this;
	}
}

