// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IFlammableInterface.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UFlammableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FIRESPREADING_API IFlammableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void TryStartBurning(AActor* InInstigator);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsBurning();
};
