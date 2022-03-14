// Copyright Epic Games, Inc. All Rights Reserved.

#include "BrunnhildeGameMode.h"
#include "BrunnhildeCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABrunnhildeGameMode::ABrunnhildeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
