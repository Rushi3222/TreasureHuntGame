// Copyright Epic Games, Inc. All Rights Reserved.

#include "treasureHuntGameMode.h"
#include "treasureHuntCharacter.h"
#include "UObject/ConstructorHelpers.h"

AtreasureHuntGameMode::AtreasureHuntGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
