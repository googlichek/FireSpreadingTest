// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FireSpreadingWindDirectionArrow.h"

#include "Game/FireSpreadingGameInstance.h"


// Sets default values
AFireSpreadingWindDirectionArrow::AFireSpreadingWindDirectionArrow()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFireSpreadingWindDirectionArrow::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFireSpreadingWindDirectionArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UFireSpreadingGameInstance* AFireSpreadingWindDirectionArrow::GetFireSpreadingGameInstance()
{
	if (FireSpreadingGameInstance)
	{
		return FireSpreadingGameInstance;
	}

	if (const UWorld* World = GetWorld())
	{
		if (UGameInstance* GameInstance = World->GetGameInstance())
		{
			FireSpreadingGameInstance = Cast<UFireSpreadingGameInstance>(GameInstance);
		}
	}

	return FireSpreadingGameInstance;
}

