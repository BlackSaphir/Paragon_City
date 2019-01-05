// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Paragon_GameInstance.generated.h"

/**
 *
 */
UCLASS()
class PARAGON_CITY_API UParagon_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UParagon_GameInstance(const FObjectInitializer& ObjectInitializer);


	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SaveGame();
};
