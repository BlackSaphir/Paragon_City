// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_SpawnPlayground.generated.h"

/**
 * 
 */
UCLASS()
class PARAGON_CITY_API UW_SpawnPlayground : public UUserWidget
{
	GENERATED_BODY()
	
public:

		UFUNCTION(BlueprintImplementableEvent)
		void Set_PlayerController();
};
