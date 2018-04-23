// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/GameUserSettings.h"
#include "Camera_Manager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PARAGON_CITY_API UCamera_Manager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCamera_Manager();

	// Component

	


	// Function


public:

	void MoveRight(float axisvalue, float RightSpeed, UCameraComponent* Camera_Component);
	void MoveForward(float axisvalue, float ForwardSpeed, UCameraComponent* Camera_Component);



	// Variable


public:

	APlayerController* PlayerController;
	UGameUserSettings* UserSettings;
	float ResolutionX;
	float ResolutionY;
	float MousepositionX;
	float MousepositionY;
	bool bLockedX = false;

	
};
