// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/FireSpreadingGameInstance.h"

#include "Data/Assets/FireSpreadingColorPaletteDataAsset.h"

FLinearColor UFireSpreadingGameInstance::GetColorFromPalette(const EColorPalette Color) const
{
	if (ColorPaletteData)
	{
		switch (Color)
		{
		case EColorPalette::None:
			return FLinearColor(0, 0, 0, 0);
		case EColorPalette::Black:
			return ColorPaletteData->Black;
		case EColorPalette::Orange:
			return ColorPaletteData->Orange;
		case EColorPalette::Green:
			return ColorPaletteData->Green;
		}
	}

	return FLinearColor(0, 0, 0, 0);;
}

void UFireSpreadingGameInstance::SetTimeToBurn(const float InTimeToBurn)
{
	TimeToBurn = InTimeToBurn;
}

void UFireSpreadingGameInstance::SetSpreadChance(const float InSpreadChance)
{
	SpreadChance = InSpreadChance;
}
