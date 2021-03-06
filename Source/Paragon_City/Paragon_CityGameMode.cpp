// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Paragon_CityGameMode.h"
#include "Paragon_CityPlayerController.h"
#include "Paragon_CityCharacter.h"
#include "UObject/ConstructorHelpers.h"

AParagon_CityGameMode::AParagon_CityGameMode()
{
#if PLATFORM_WINDOWS
	// use our custom PlayerController class
	PlayerControllerClass = AParagon_CityPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
#endif

#if PLATFORM_IOS

	PlayerControllerClass = AParagon_CityPlayerController::StaticClass();

	static ConstructorHelpers::FClassFinder<APawn> BuiltManager(TEXT("/Game/Blueprints/Character/BP_Built_Manager"));
	if (BuiltManager.Class != NULL)
	{
		DefaultPawnClass = BuiltManager.Class;

	}

#endif
}