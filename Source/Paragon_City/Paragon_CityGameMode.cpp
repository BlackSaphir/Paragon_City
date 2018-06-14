// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Paragon_CityGameMode.h"
#include "Paragon_CityCharacter.h"
#include "Built_Manager.h"
#include "Paragon_CityPlayerController.h"
#include "UObject/ConstructorHelpers.h"

AParagon_CityGameMode::AParagon_CityGameMode()
{
#if PLATFORM_WINDOWS
	
	const ConstructorHelpers::FObjectFinder<UClass> playerController_BP(TEXT("Class'/Game/Blueprints/Character/BP_Paragon_CityPlayerController.BP_Paragon_CityPlayerController_C'"));

	PlayerControllerClass = playerController_BP.Object;
	
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
