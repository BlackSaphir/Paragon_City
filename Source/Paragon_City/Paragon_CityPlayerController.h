// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Built_Manager.h"
#include "GameView_Camera.h"
#include "W_Building.h"
#include "Paragon_CityGameMode.h"
#include "W_SpawnPlayground.h"
#include "ARTrackable.h"
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

	UFUNCTION(BlueprintCallable)
		void SpawnARFloor();


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
	float inputX;
	float InputY;
	float angleDiff;
	float dist;

	int fingerCount = 0;

	FVector worldLoc;
	FVector worldDir;
	FVector touchDIr;
	FVector ForwardVectorManipulated;
	FVector spawnLocation;


	class AParagon_CityGameMode *myGameMode;
	APawn* defaultPawn;
	AGameView_Camera * gameViewCamera;

	UClass* builtManager_Class;
	TSubclassOf<APawn> builtManagerSubClass;
	ABuilt_Manager* builtManagerPawn;

	UClass* built_Widget_Class;
	TSubclassOf<UUserWidget> building_Widget_SubClass;
	UW_Building* building_Widget;

	UClass* spawnPlayground_Widget_Class;
	TSubclassOf<UUserWidget> spawnPlayground_SubClass;
	UW_SpawnPlayground* spawnPlayground_Widget;


	UPrimitiveComponent* primitive_Comp;
	TArray<UARPlaneGeometry*> trackedGeometries;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsPressed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bMovingBuilding;

	UPROPERTY(EditAnywhere, Category = Touch)
		float distance = 20.0f;

	UPROPERTY(EditAnywhere, Category = Touch)
		float speedMultiplier = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsARSession = false;
};


