// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Paragon_CityGameMode.generated.h"

UCLASS(minimalapi)
class AParagon_CityGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AParagon_CityGameMode();
	void SetDefaultPawnClass(TSubclassOf<APawn> pawn);
};



