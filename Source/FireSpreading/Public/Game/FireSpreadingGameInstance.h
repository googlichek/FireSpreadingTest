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
	float GetNumberOfObjects() const { return NumberOfObjects; }

	UFUNCTION(BlueprintCallable)
	void SetNumberOfObjects(float InNumberOfObjects);

	UFUNCTION(BlueprintCallable)
	FVector GetWindDirection() const { return WindDirection; }

	UFUNCTION(BlueprintCallable)
	void SetWindDirection(FVector InWindDirection);

	UFUNCTION(BlueprintCallable)
	float GetWindSpeed() const { return WindSpeed; }

	UFUNCTION(BlueprintCallable)
	void SetWindSpeed(float InWindSpeed);

	UFUNCTION(BlueprintCallable)
	float GetTimeToBurn() const { return TimeToBurn; }

	UFUNCTION(BlueprintCallable)
	void SetTimeToBurn(float InTimeToBurn);

	UFUNCTION(BlueprintCallable)
	float GetSpreadChance() const { return SpreadChance; }

	UFUNCTION(BlueprintCallable)
	void SetSpreadChance(float InSpreadChance);

	UFUNCTION(BlueprintCallable)
	float GetSpreadAreaRadius() const { return SpreadAreaRadius; }

	UFUNCTION(BlueprintCallable)
	void SetSpreadAreaRadius(float InSpreadAreaRadius);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UFireSpreadingColorPaletteDataAsset> ColorPaletteData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = 100, ClampMax = 5000))
	int32 NumberOfObjects = 1000;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector WindDirection = FVector::ForwardVector;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = 0, ClampMax = 1000))
	float WindSpeed = 150.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = 1, ClampMax = 100))
	float TimeToBurn = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = 50, ClampMax = 500))
	float SpreadAreaRadius = 250.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = 0.0f, ClampMax = 1.0f))
	float SpreadChance = 0.5f;
};
