// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Built_Manager.h"
#include "GameView_Camera.h"
#include "W_Building.h"
#include "Paragon_CityGameMode.h"
#include "ARTrackable.h"
#include "W_SpawnPlayground.h"
#include "Paragon_CityPlayerController.generated.h"


class UW_AR;
//class UW_SpawnPlayground;


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
	virtual bool InputTouch(uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, float Force, FDateTime DeviceTimestamp, uint32 TouchpadIndex) override;
	void MoveRightTouch();
	void MoveLeftTouch();
	void MoveUpTouch();
	void MoveDownTouch();
	void Zoom();
	void Move();
	bool LineTrace(UWorld*, const FVector&, const FVector&, TArray<FHitResult>&, ECollisionChannel, bool);

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SpawnARFloor();

	UFUNCTION(BlueprintCallable)
		void CreateBuildingWidget();

	UFUNCTION(BlueprintCallable)
		void RemoveFloorWidget();


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

	UWorld* world;
	ECollisionChannel collisionChannel = ECC_WorldDynamic;
	TArray <FHitResult> hitResult_Building;

	FVector worldLoc;
	FVector worldDir;
	FVector touchDIr;
	FVector ForwardVectorManipulated;
	FVector spawnLocation_Playground;


	class AParagon_CityGameMode *myGameMode;
	APawn* defaultPawn;
	AGameView_Camera * gameViewCamera;

	UClass* builtManager_Class;
	TSubclassOf<APawn> builtManagerSubClass;

	UClass* built_Widget_Class;
	TSubclassOf<UUserWidget> building_Widget_SubClass;
	UW_Building* building_Widget;

	UClass* AR_Widget_Class;
	TSubclassOf<UUserWidget> AR_Widget_SubClass;

	UClass* spawnPlayground_Widget_Class;
	TSubclassOf<UUserWidget> spawnPlayground_SubClass;
	UW_SpawnPlayground* spawnPlayground_Widget;


	UPrimitiveComponent* primitive_Comp;
	TArray<UARPlaneGeometry*> trackedGeometries;
	UARPlaneGeometry* plane;


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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ABuilt_Manager* BuiltManagerPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector Plane_Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator Plane_Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UARTrackedGeometry* Plane;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bStartMoveBuilding;


};


