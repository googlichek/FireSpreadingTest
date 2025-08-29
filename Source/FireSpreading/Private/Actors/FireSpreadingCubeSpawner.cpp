// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FireSpreadingCubeSpawner.h"

#include "Actors/FireSpreadingFlammableActor.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "Game/FireSpreadingGameInstance.h"


AFireSpreadingCubeSpawner::AFireSpreadingCubeSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFireSpreadingCubeSpawner::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SpawnCubeBatch();
}

void AFireSpreadingCubeSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void AFireSpreadingCubeSpawner::SpawnCubeBatch()
{
	if (CubeCount <= GetGameInstance()->GetNumberOfObjects() - 1)
	{
		FEnvQueryRequest Request(SpawnPositionQuery, this);
		Request.Execute(EEnvQueryRunMode::RandomBest5Pct, this, &ThisClass::OnSpawnQueryCompleted);
	}
}

void AFireSpreadingCubeSpawner::OnSpawnQueryCompleted(TSharedPtr<FEnvQueryResult> Result)
{
	const FEnvQueryResult* QueryResult = Result.Get();
	if (!QueryResult->IsSuccessful())
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn EQS Query Failed!"));
		return;
	}

	TArray<FVector> Locations;
	QueryResult->GetAllAsLocations(Locations);

	if (CubeClass)
	{
		for (const FVector& Location : Locations)
		{
			if (CubeCount <= GetGameInstance()->GetNumberOfObjects() - 1)
			{
				CubeCount++;

				FActorSpawnParameters SpawnParameters;
				SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

				const float JitterX = FMath::RandRange(-SpawnJitterOffset, SpawnJitterOffset);
				const float JitterY = FMath::RandRange(-SpawnJitterOffset, SpawnJitterOffset);

				const FVector FinalLocation = Location + FVector(JitterX, JitterY, CubeSize * 0.5f);

				AFireSpreadingFlammableActor* NewCube =
					GetWorld()->SpawnActor<AFireSpreadingFlammableActor>(CubeClass, FinalLocation, FRotator::ZeroRotator, SpawnParameters);
			}
		}
	}
}

UFireSpreadingGameInstance* AFireSpreadingCubeSpawner::GetGameInstance()
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

