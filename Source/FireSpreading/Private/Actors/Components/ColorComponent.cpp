// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Components/ColorComponent.h"

#include "Game/FireSpreadingGameInstance.h"


UColorComponent::UColorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UColorComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UColorComponent::CreateAndAssignDynamicMaterialInstances(UPrimitiveComponent* InMesh, AActor* InOwner)
{
	TArray<UMaterialInterface*> Materials;
	InMesh->GetUsedMaterials(Materials);

	int Index = 0;
	for (const auto Material : Materials)
	{
		UMaterialInstanceDynamic* DynamicMI = UMaterialInstanceDynamic::Create(Material, InOwner);
		InMesh->SetMaterial(Index, DynamicMI);
		Index++;

		DynamicMIs.Add(DynamicMI);
	}
}

void UColorComponent::SetInitialColor()
{
	const FLinearColor Color = GetGameInstance()->GetColorFromPalette(InitialColor);
	for (const auto DynamicMI : DynamicMIs)
	{
		DynamicMI->SetVectorParameterValue(ColorPropertyName, Color);
	}
}

void UColorComponent::SetBurnProgressColor(const float InProgress, const bool ShouldForceUpdate)
{
	SinceStartedBurningTicks++;

	if (ShouldForceUpdate || SinceStartedBurningTicks % UpdateIntervalTicks == 0)
	{
		const FLinearColor StartColor = GetGameInstance()->GetColorFromPalette(BurningStartColor);
		const FLinearColor EndColor = GetGameInstance()->GetColorFromPalette(BurningEndColor);

		const FLinearColor CurrentColor = FLinearColor::LerpUsingHSV(StartColor, EndColor, InProgress);
		for (const auto DynamicMI : DynamicMIs)
		{
			DynamicMI->SetVectorParameterValue(ColorPropertyName, CurrentColor);
		}
	}
}

UFireSpreadingGameInstance* UColorComponent::GetGameInstance()
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

