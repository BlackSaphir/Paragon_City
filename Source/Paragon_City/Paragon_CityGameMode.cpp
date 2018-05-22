// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Paragon_CityGameMode.h"
#include "Paragon_CityCharacter.h"
#include "Built_Manager.h"
#include "Paragon_CityPlayerController.h"
#include "UObject/ConstructorHelpers.h"

AParagon_CityGameMode::AParagon_CityGameMode()
{
#if PLATFORM_WINDOWS
	
	PlayerControllerClass = AParagon_CityPlayerController::StaticClass();
	
#endif

#if PLATFORM_IOS

	PlayerControllerClass = AParagon_CityPlayerController::StaticClass();

	

#endif
    
#if PLATFORM_MAC
    
    PlayerControllerClass = AParagon_CityPlayerController::StaticClass();

#endif
    
}


void AParagon_CityGameMode::SetDefaultPawnClass(TSubclassOf<APawn> pawn)
{
	DefaultPawnClass = pawn;
}
