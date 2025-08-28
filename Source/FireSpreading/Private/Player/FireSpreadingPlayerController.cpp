// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FireSpreadingPlayerController.h"

void AFireSpreadingPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}
