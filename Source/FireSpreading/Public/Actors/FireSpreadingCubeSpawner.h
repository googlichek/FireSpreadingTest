// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/FireSpreadingActorBase.h"
#include "FireSpreadingCubeSpawner.generated.h"

struct FEnvQueryResult;
class UEnvQuery;
class UFireSpreadingGameInstance;
class AFireSpreadingFlammableActor;

UCLASS()
class FIRESPREADING_API AFireSpreadingCubeSpawner : public AFireSpreadingActorBase
{
	GENERATED_BODY()

public:
	AFireSpreadingCubeSpawner();

	virtual void Tick(float DeltaSeconds) override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AFireSpreadingFlammableActor> CubeClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UEnvQuery> SpawnPositionQuery;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = 0, ClampMax = 150))
	float SpawnJitterOffset = 50.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = 0, ClampMax = 150))
	float CubeSize = 50.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = 0, ClampMax = 50))
	int32 SpawnBatch = 5;

	UPROPERTY(VisibleAnywhere, Transient)
	TObjectPtr<UFireSpreadingGameInstance> FireSpreadingGameInstance = nullptr;

	UPROPERTY(VisibleAnywhere, Transient)
	int32 CubeCount = 0;

	virtual void BeginPlay() override;

	void SpawnCubeBatch();

	void OnSpawnQueryCompleted(TSharedPtr<FEnvQueryResult> Result);

	UFireSpreadingGameInstance* GetGameInstance();
};
