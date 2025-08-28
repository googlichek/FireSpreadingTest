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
	void SetBurnProgressColor(float InProgress);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EColorPalette InitialColor = EColorPalette::Green;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EColorPalette BurningStartColor = EColorPalette::Orange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EColorPalette BurningEndColor = EColorPalette::Black;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName ColorPropertyName = FName("Color");

	UPROPERTY(VisibleAnywhere, Transient)
	TArray<TObjectPtr<UMaterialInstanceDynamic>> DynamicMIs;

	UPROPERTY(VisibleAnywhere, Transient)
	TObjectPtr<UFireSpreadingGameInstance> FireSpreadingGameInstance = nullptr;

	virtual void BeginPlay() override;

	UFireSpreadingGameInstance* GetGameInstance();
};
