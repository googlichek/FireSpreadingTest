// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/Enums/EColorPalette.h"
#include "ColorComponent.generated.h"


class UFireSpreadingGameInstance;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIRESPREADING_API UColorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UColorComponent();

	void CreateAndAssignDynamicMaterialInstances(UPrimitiveComponent* InMesh, AActor* InOwner);

	void SetInitialColor();
	void SetBurnProgressColor(float InProgress, bool ShouldForceUpdate = false);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EColorPalette InitialColor = EColorPalette::Green;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EColorPalette BurningStartColor = EColorPalette::Orange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EColorPalette BurningEndColor = EColorPalette::Black;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = 1, ClampMax = 60))
	int32 UpdateIntervalTicks = 6;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName ColorPropertyName = FName("Color");

	UPROPERTY(VisibleAnywhere, Transient)
	TArray<TObjectPtr<UMaterialInstanceDynamic>> DynamicMIs;

	UPROPERTY(VisibleAnywhere, Transient)
	TObjectPtr<UFireSpreadingGameInstance> FireSpreadingGameInstance = nullptr;

	UPROPERTY(VisibleAnywhere, Transient)
	int32 SinceStartedBurningTicks = 0;

	virtual void BeginPlay() override;

	UFireSpreadingGameInstance* GetGameInstance();
};
