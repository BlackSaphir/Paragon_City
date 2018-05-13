// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Built_Manager.h"
#include "Paragon_CityPlayerController.generated.h"

UCLASS()
class AParagon_CityPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AParagon_CityPlayerController();

	// Function

private:


	virtual void PlayerTick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual bool InputTouch(uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, FDateTime DeviceTimestamp, uint32 TouchpadIndex) override;
	void MoveRightTouch();
	void MoveLeftTouch();
	void Pressed(const ETouchIndex::Type FingerIndex, FVector Location);


	// Variable

private:

	ABuilt_Manager* builtManager;
	FVector worldLocStart;
	FVector worldLocEnd;
	FVector worldDir;
	FVector2D touchStart;
	FVector2D touchEnd;
	FVector2D inputVector;
	FVector2D Penis;
	FVector finalLocation;

	float inputX;
	float InputY;
	float breakVectorX;
	float breakVectorY;

	bool bIsPressed;
	bool bIsCurrentlyPressed;
	bool bDoOnce;
	
	
};


