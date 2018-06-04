// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Built_Manager.h"
#include "GameView_Camera.h"
#include "W_Building.h"
#include "Paragon_CityGameMode.h"
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
	void MoveUpTouch();
	void MoveDownTouch();
	void Zoom();
	void Move();

public:





	// Variable

private:
	FVector2D touchStart;
	FVector2D touchEnd;
	FVector2D inputVector;
	FVector2D finalLocation;

	FVector2D firstFingerTouchStart;
	FVector2D firstFingerTouchEnd;
	FVector2D secondFingerTouchStart;
	FVector2D secondFingerTouchEnd;

	float screenX;
	float screenY;
	FVector worldLoc;
	FVector worldDir;
	FVector touchDIr;

	FVector ForwardVectorManipulated;

	float inputX;
	float InputY;

	float angleDiff;
	float dist;
	int fingerCount = 0;
	class AParagon_CityGameMode *myGameMode;
	APawn* defaultPawn;
	AGameView_Camera * gameViewCamera;
	UW_Building* building_Widget;


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsPressed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bMovingBuilding;

	UPROPERTY(EditAnywhere, Category = Touch)
		float distance = 20.0f;

	UPROPERTY(EditAnywhere, Category = Touch)
		float speedMultiplier = 0.1f;

	// TSoftClassPtr? 
	UClass* builtManager;
	TSubclassOf<APawn> builtManagerSubClass;
	ABuilt_Manager* builtManagerPawn;
	UPrimitiveComponent* primitive_Comp;
};


