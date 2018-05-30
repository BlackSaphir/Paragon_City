// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "GameView_Camera.generated.h"

/**
 *
 */
UCLASS()
class PARAGON_CITY_API AGameView_Camera : public ACameraActor
{
	GENERATED_BODY()


		// Functions

		void BeginPlay() override;
};
