// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FireSpreadingFlammableActor.h"

#include "Actors/Components/ColorComponent.h"
#include "Actors/Interface/IFlammableInterface.h"
#include "Components/SphereComponent.h"
#include "Game/FireSpreadingGameInstance.h"


AFireSpreadingFlammableActor::AFireSpreadingFlammableActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	Mesh->SetSimulatePhysics(true);
	Mesh->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	SetRootComponent(Mesh);

	ColorComponent = CreateDefaultSubobject<UColorComponent>(TEXT("ColorComponent"));

	SpreadAreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	SpreadAreaSphere->SetupAttachment(RootComponent);
	SpreadAreaSphere->SetSphereRadius(SpreadAreaRadius);
	SpreadAreaSphere->SetSimulatePhysics(false);
	SpreadAreaSphere->SetEnableGravity(false);
	SpreadAreaSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	SpreadAreaSphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	SpreadAreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

// Called when the game starts or when spawned
void AFireSpreadingFlammableActor::BeginPlay()
{
	Super::BeginPlay();

	SpreadAreaSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereOverlap);
	SpreadAreaSphere->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnSphereEndOverlap);

	Mesh->OnClicked.AddDynamic(this, &ThisClass::OnMouseClicked);

	CurrentHealth = MaxHealth;

	ColorComponent->CreateAndAssignDynamicMaterialInstances(Mesh, this);
	ColorComponent->SetInitialColor();
}

void AFireSpreadingFlammableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsInFlames)
	{
		return;
	}

	SinceStartedBurningTicks++;

	if (CurrentHealth > 0)
	{
		const float BurnedOffHealth = MaxHealth * DeltaTime / GetGameInstance()->GetTimeToBurn();
		CurrentHealth -= BurnedOffHealth;

		const float BurnProgress = (MaxHealth - CurrentHealth) / MaxHealth;
		ColorComponent->SetBurnProgressColor(BurnProgress);

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
	}
	else
	{
		OverlappingAndNotBurningFlammables.Empty();
	}
}

void AFireSpreadingFlammableActor::TryStartBurning_Implementation(AActor* InInstigator)
{
	const float CurrentChance = FMath::RandRange(0.0f, 1.0f);

	if (CurrentChance <= GetGameInstance()->GetSpreadChance())
	{
		StartBurning();
	}
}

#if WITH_EDITOR
void AFireSpreadingFlammableActor::PostEditChangeProperty(struct FPropertyChangedEvent& Event)
{
	Super::PostEditChangeProperty(Event);
}
#endif

void AFireSpreadingFlammableActor::OnSphereOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
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

