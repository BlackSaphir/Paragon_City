#include "Paragon_GameInstance.h"
// Fill out your copyright notice in the Description page of Project Settings.

#include "Paragon_GameInstance.h"
#include "Paragon_SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Built_Manager.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"



UParagon_GameInstance::UParagon_GameInstance()
	: SaveSlot(TEXT("SaveGame")),
	SaveUserIndex(0)
{
}

void UParagon_GameInstance::CheckSaveGame()
{
	CurrentSaveGame = nullptr;

	if (UGameplayStatics::DoesSaveGameExist(SaveSlot, SaveUserIndex))
	{
		CurrentSaveGame = Cast<UParagon_SaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlot, SaveUserIndex));		
		if (CurrentSaveGame == NULL)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("No Save Game")));

		}
	}
	else
	{
		CurrentSaveGame = Cast<UParagon_SaveGame>(UGameplayStatics::CreateSaveGameObject(UParagon_SaveGame::StaticClass()));
	}


}

void UParagon_GameInstance::WriteSaveGame()
{
	UGameplayStatics::SaveGameToSlot(CurrentSaveGame, SaveSlot, SaveUserIndex);
}

void UParagon_GameInstance::SetVariables()
{
	//builtManager =
}
