// Fill out your copyright notice in the Description page of Project Settings.

#include "Paragon_GameInstance.h"
#include "Paragon_SaveGame.h"
#include "Kismet/GameplayStatics.h"



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
