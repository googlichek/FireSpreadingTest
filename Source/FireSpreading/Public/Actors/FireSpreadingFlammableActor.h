// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/FireSpreadingActorBase.h"
#include "Interface/IFlammable.h"
#include "FireSpreadingFlammableActor.generated.h"

UCLASS()
class FIRESPREADING_API AFireSpreadingFlammableActor :
	public AFireSpreadingActorBase,
	public IFlammable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFireSpreadingFlammableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
