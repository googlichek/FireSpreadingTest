// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FireSpreadingWidgetBase.h"

#include "Game/FireSpreadingGameInstance.h"

UFireSpreadingGameInstance* UFireSpreadingWidgetBase::GetFireSpreadingGameInstance()
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
