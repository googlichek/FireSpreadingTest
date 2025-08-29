// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/FireSpreadingActorBase.h"
#include "FireSpreadingWindDirectionArrow.generated.h"

class UFireSpreadingGameInstance;

UCLASS()
class FIRESPREADING_API AFireSpreadingWindDirectionArrow : public AFireSpreadingActorBase
{
	GENERATED_BODY()

public:
	AFireSpreadingWindDirectionArrow();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UFireSpreadingGameInstance* GetFireSpreadingGameInstance();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Transient)
	TObjectPtr<UFireSpreadingGameInstance> FireSpreadingGameInstance = nullptr;
};
