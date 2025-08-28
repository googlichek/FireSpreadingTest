// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EColorPalette : uint8
{
	None UMETA(DisplayName = "None"),
	Black UMETA(DisplayName = "Black"),
	Orange UMETA(DisplayName = "Orange"),
	Green UMETA(DisplayName = "Green"),
};
