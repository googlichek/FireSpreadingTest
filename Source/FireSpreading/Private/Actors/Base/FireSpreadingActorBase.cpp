// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Base/FireSpreadingActorBase.h"


// Sets default values
AFireSpreadingActorBase::AFireSpreadingActorBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFireSpreadingActorBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFireSpreadingActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

