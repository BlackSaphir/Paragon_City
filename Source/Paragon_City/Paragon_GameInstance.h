// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Paragon_GameInstance.generated.h"

class UParagon_SaveGame;


UCLASS()
class PARAGON_CITY_API UParagon_GameInstance : public UGameInstance
{
	GENERATED_BODY()


		//Function

public:

	UParagon_GameInstance();

	UFUNCTION(BlueprintCallable)
		void CheckSaveGame();

	UFUNCTION(BlueprintCallable)
		void WriteSaveGame();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void GetInformation();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void SaveStruct();


		// Variable

public:

	UPROPERTY(BlueprintReadWrite)
		FString SaveSlot;

	UPROPERTY(BlueprintReadWrite)
		int32 SaveUserIndex;

	UPROPERTY(BlueprintReadWrite)
		UParagon_SaveGame* CurrentSaveGame;
};
