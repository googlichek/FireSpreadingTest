// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FireSpreadingColorPaletteDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, Const)
class FIRESPREADING_API UFireSpreadingColorPaletteDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Color")
	FLinearColor Black;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Color")
	FLinearColor Orange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Color")
	FLinearColor Green;
};
