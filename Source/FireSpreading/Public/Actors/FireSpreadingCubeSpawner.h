// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/FireSpreadingActorBase.h"
#include "FireSpreadingCubeSpawner.generated.h"

UCLASS()
class FIRESPREADING_API AFireSpreadingCubeSpawner : public AFireSpreadingActorBase
{
	GENERATED_BODY()

public:
	AFireSpreadingCubeSpawner();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};
