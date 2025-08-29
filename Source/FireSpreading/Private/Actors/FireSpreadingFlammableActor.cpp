// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FireSpreadingFlammableActor.h"

#include "Actors/Components/ColorComponent.h"
#include "Actors/Interface/IFlammableInterface.h"
#include "Components/SphereComponent.h"
#include "FireSpreading/FireSpreading.h"
#include "Game/FireSpreadingGameInstance.h"


AFireSpreadingFlammableActor::AFireSpreadingFlammableActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	Mesh->SetSimulatePhysics(true);
	Mesh->SetEnableGravity(false);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	Mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	Mesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	Mesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	SetRootComponent(Mesh);

	ColorComponent = CreateDefaultSubobject<UColorComponent>(TEXT("ColorComponent"));

	SpreadAreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	SpreadAreaSphere->SetupAttachment(RootComponent);
	SpreadAreaSphere->SetSimulatePhysics(false);
	SpreadAreaSphere->SetEnableGravity(false);
	SpreadAreaSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	SpreadAreaSphere->SetCollisionResponseToChannel(ECC_Flammable, ECR_Overlap);
	SpreadAreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	bGenerateOverlapEventsDuringLevelStreaming = true;
}

// Called when the game starts or when spawned
void AFireSpreadingFlammableActor::BeginPlay()
{
	Super::BeginPlay();

	SetActorTickEnabled(false);

	SpreadAreaSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereOverlap);
	SpreadAreaSphere->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnSphereEndOverlap);

	Mesh->OnClicked.AddDynamic(this, &ThisClass::OnMouseClicked);

	CurrentHealth = MaxHealth;

	ColorComponent->CreateAndAssignDynamicMaterialInstances(Mesh, this);
	ColorComponent->SetInitialColor();

	UpdateSpreadAreaRadius();
	UpdateSpreadAreaSphereLocation();
}

void AFireSpreadingFlammableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsInFlames)
	{
		return;
	}

	if (CurrentHealth <= 0)
	{
		return;
	}

	SinceStartedBurningTicks++;

	if (CurrentHealth > 0)
	{
		UpdateSpreadAreaRadius();
		UpdateSpreadAreaSphereLocation();

		const float BurnedOffHealth = MaxHealth * DeltaTime / GetGameInstance()->GetTimeToBurn();
		CurrentHealth -= BurnedOffHealth;

		const float BurnProgress = (MaxHealth - CurrentHealth) / MaxHealth;
		ColorComponent->SetBurnProgressColor(BurnProgress, CurrentHealth <= 0);

		if (SinceStartedBurningTicks % TryBurnIntervalTicks == 0)
		{
			for (const auto Flammable : OverlappingAndNotBurningFlammables)
			{
				if (!Flammable->IsBurning_Implementation())
				{
					Flammable->TryStartBurning_Implementation(this);
				}
			}
		}

		if (CurrentHealth <= 0)
		{
			SetActorTickEnabled(false);
			Mesh->SetSimulatePhysics(false);
			Mesh->SetGenerateOverlapEvents(false);
			SpreadAreaSphere->SetGenerateOverlapEvents(false);
			OverlappingAndNotBurningFlammables.Empty();
		}
	}
}

void AFireSpreadingFlammableActor::TryStartBurning_Implementation(AActor* InInstigator)
{
	const float CurrentChance = FMath::RandRange(0.0f, 1.0f);
	const float SpreadChance = FMath::Clamp(GetGameInstance()->GetSpreadChance(), 0.0f, 1.0f);

	if (CurrentChance <= SpreadChance)
	{
		StartBurning();
	}
}

void AFireSpreadingFlammableActor::UpdateSpreadAreaRadius()
{
	const float Radius = GetGameInstance()->GetSpreadAreaRadius();
	SpreadAreaSphere->SetSphereRadius(Radius);
}

void AFireSpreadingFlammableActor::UpdateSpreadAreaSphereLocation()
{
	const FVector WindDirection = GetGameInstance()->GetWindDirection().GetSafeNormal();
	const float WindSpeed = GetGameInstance()->GetWindSpeed();

	const FVector WindOffset = WindDirection * WindSpeed;

	const FVector LocalWindOffset = GetActorTransform().InverseTransformVector(WindOffset);
	SpreadAreaSphere->SetRelativeLocation(LocalWindOffset);
}

void AFireSpreadingFlammableActor::OnSphereOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (CurrentHealth <= 0)
	{
		return;
	}

	 if (OtherActor && OtherActor != this)
	{
		if (OtherActor->Implements<UFlammableInterface>())
		{
			if (const TScriptInterface<IFlammableInterface> FlammableInterface = TScriptInterface<IFlammableInterface>(OtherActor))
			{
				if (!FlammableInterface->IsBurning_Implementation())
				{
					if (!OverlappingAndNotBurningFlammables.Contains(FlammableInterface))
					{
						OverlappingAndNotBurningFlammables.Add(FlammableInterface);
					}
				}
			}
		}
	}
}

void AFireSpreadingFlammableActor::OnSphereEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	if (CurrentHealth <= 0)
	{
		return;
	}

	if (OtherActor && OtherActor != this)
	{
		if (OverlappingAndNotBurningFlammables.Contains(OtherActor))
		{
			OverlappingAndNotBurningFlammables.Remove(OtherActor);
		}
	}
}

void AFireSpreadingFlammableActor::OnMouseClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	StartBurning();
}

void AFireSpreadingFlammableActor::StartBurning()
{
	SetActorTickEnabled(true);

	IsInFlames = true;

	const float BurnProgress = (MaxHealth - CurrentHealth) / MaxHealth;
	ColorComponent->SetBurnProgressColor(BurnProgress);
}

UFireSpreadingGameInstance* AFireSpreadingFlammableActor::GetGameInstance()
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

