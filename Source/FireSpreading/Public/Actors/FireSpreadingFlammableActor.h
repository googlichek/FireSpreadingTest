// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/FireSpreadingActorBase.h"
#include "Interface/IFlammableInterface.h"
#include "FireSpreadingFlammableActor.generated.h"

class UColorComponent;
class UFireSpreadingGameInstance;
class USphereComponent;

UCLASS()
class FIRESPREADING_API AFireSpreadingFlammableActor :
	public AFireSpreadingActorBase,
	public IFlammableInterface
{
	GENERATED_BODY()

public:
	AFireSpreadingFlammableActor();

	virtual void Tick(float DeltaTime) override;

	// Flammable Interface
	virtual void TryStartBurning_Implementation(AActor* InInstigator) override;
	virtual bool IsBurning_Implementation() override { return IsInFlames && CurrentHealth > 0; };

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& Event) override;
#endif

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UColorComponent> ColorComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USphereComponent> SpreadAreaSphere;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = 1, ClampMax = 60))
	int32 TryBurnIntervalTicks = 15;

	UPROPERTY(VisibleAnywhere, Transient)
	TArray<TScriptInterface<IFlammableInterface>> OverlappingAndNotBurningFlammables;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = 0, ClampMax = 100))
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere, Transient)
	float CurrentHealth = 100;

	UPROPERTY(VisibleAnywhere, Transient)
	int32 SinceStartedBurningTicks = 0;

	UPROPERTY(VisibleAnywhere, Transient)
	bool IsInFlames = false;

	UPROPERTY(VisibleAnywhere, Transient)
	TObjectPtr<UFireSpreadingGameInstance> FireSpreadingGameInstance = nullptr;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int OtherBodyIndex);

	UFUNCTION()
	void OnMouseClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	void StartBurning();

	UFireSpreadingGameInstance* GetGameInstance();
};
