// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FireSpreadingWindDirectionArrow.h"

#include "Game/FireSpreadingGameInstance.h"


AFireSpreadingWindDirectionArrow::AFireSpreadingWindDirectionArrow()
{
	PrimaryActorTick.bCanEverTick = true;
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

