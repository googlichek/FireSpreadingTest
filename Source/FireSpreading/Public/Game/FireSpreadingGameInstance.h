// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Enums/EColorPalette.h"
#include "Engine/GameInstance.h"
#include "FireSpreadingGameInstance.generated.h"

class UFireSpreadingColorPaletteDataAsset;
/**
 * 
 */
UCLASS()
class FIRESPREADING_API UFireSpreadingGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	FLinearColor GetColorFromPalette(EColorPalette Color) const;

	UFUNCTION(BlueprintCallable)
	float GetTimeToBurn() const { return TimeToBurn; };

	UFUNCTION(BlueprintCallable)
	void SetTimeToBurn(float InTimeToBurn);

	UFUNCTION(BlueprintCallable)
	float GetSpreadChance() const { return SpreadChance; };

	UFUNCTION(BlueprintCallable)
	void SetSpreadChance(float InSpreadChance);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UFireSpreadingColorPaletteDataAsset> ColorPaletteData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = 1, ClampMax = 100))
	float TimeToBurn = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = 0.0f, ClampMax = 0.5f))
	float SpreadChance = 0.5f;
};
