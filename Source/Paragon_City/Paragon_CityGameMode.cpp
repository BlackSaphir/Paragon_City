// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Paragon_CityGameMode.h"
#include "Paragon_CityCharacter.h"
#include "Built_Manager.h"
#include "Kismet/GameplayStatics.h"
#include "Paragon_CityPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"


AParagon_CityGameMode::AParagon_CityGameMode()
{

#if PLATFORM_WINDOWS

	const ConstructorHelpers::FObjectFinder<UClass> playerController_BP(TEXT("Class'/Game/Blueprints/Character/BP_Paragon_CityPlayerController.BP_Paragon_CityPlayerController_C'"));

	PlayerControllerClass = playerController_BP.Object;


#endif

	#if PLATFORM_IOS

	const ConstructorHelpers::FObjectFinder<UClass> playerController_BP(TEXT("Class'/Game/Blueprints/Character/BP_Paragon_CityPlayerController.BP_Paragon_CityPlayerController_C'"));

	PlayerControllerClass = playerController_BP.Object;

	// Check for ARKit 1.0
	#ifdef __IPHONE_11_0
	#define SUPPORTS_ARKIT_1_0 1
	support_AR = true;
	#else
	#define SUPPORTS_ARKIT_1_0 0
	#endif

	// Check for ARKit 1.5
	#ifdef __IPHONE_11_3
	#define SUPPORTS_ARKIT_1_5 1
	support_AR = true;
	#else
	#define SUPPORTS_ARKIT_1_5 0
	#endif

	// Check for ARKit 2.0
	#ifdef __IPHONE_12_0
	#define SUPPORTS_ARKIT_2_0 1
	support_AR = true;
	#else
	#define SUPPORTS_ARKIT_2_0 0
	#endif

	#else

	// No ARKit support
	#define SUPPORTS_ARKIT_1_0 0
	#define SUPPORTS_ARKIT_1_5 0
	#define SUPPORTS_ARKIT_2_0 0

	support_AR = false;


#endif

#if PLATFORM_MAC

	const ConstructorHelpers::FObjectFinder<UClass> playerController_BP(TEXT("Class'/Game/Blueprints/Character/BP_Paragon_CityPlayerController.BP_Paragon_CityPlayerController_C'"));

	PlayerControllerClass = playerController_BP.Object;

#endif

#if PLATFORM_ANDROID

	const ConstructorHelpers::FObjectFinder<UClass> playerController_BP(TEXT("Class'/Game/Blueprints/Character/BP_Paragon_CityPlayerController.BP_Paragon_CityPlayerController_C'"));

	PlayerControllerClass = playerController_BP.Object;

#endif

}


void AParagon_CityGameMode::SetDefaultPawnClass(TSubclassOf<APawn> pawn)
{
	DefaultPawnClass = pawn;
}

void AParagon_CityGameMode::PauseGame(bool PauseGameState)
{
	UWorld* world = GetWorld();

	if (PauseGameState == true)
	{
		UGameplayStatics::SetGamePaused(world, PauseGameState);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("True Pause")));

	}
	else if (PauseGameState == false)
	{
		UGameplayStatics::SetGamePaused(world, PauseGameState);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("False Pause")));

	}
}
