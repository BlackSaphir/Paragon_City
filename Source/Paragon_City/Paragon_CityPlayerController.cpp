// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Paragon_CityPlayerController.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"

AParagon_CityPlayerController::AParagon_CityPlayerController()
{
	bShowMouseCursor = true;
	builtManager = NewObject<ABuilt_Manager>();
}


void AParagon_CityPlayerController::BeginPlay()
{
	Super::BeginPlay();
	builtManager = NewObject<ABuilt_Manager>();
}

void AParagon_CityPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bIsPressed == true)
	{
		GetInputTouchState(ETouchIndex::Touch1, inputVector.X, inputVector.Y, bIsCurrentlyPressed);

		MoveRightTouch();
		MoveLeftTouch();
	}
}


//bool AParagon_CityPlayerController::InputTouch(uint32 Handle, ETouchType::Type Type, const FVector2D & TouchLocation, FDateTime DeviceTimestamp, uint32 TouchpadIndex)
//{
//	switch (Type)
//	{
//	case ETouchType::Began:
//		bDoOnce = true;
//		DeprojectScreenPositionToWorld(TouchLocation.X, TouchLocation.Y, worldLoc, worldDir);
//
//		Pressed(ETouchIndex::Touch1, worldLoc);
//	case ETouchType::Moved:
//		break;
//	case ETouchType::Stationary:
//		break;
//	case ETouchType::Ended:
//		DeprojectScreenPositionToWorld(TouchLocation.X, TouchLocation.Y, worldLoc, worldDir);
//
//		Released(ETouchIndex::Touch1, worldLoc);
//	case ETouchType::NumTypes:
//		break;
//	default:
//		break;
//	}
//
//
//	return false;
//}


void AParagon_CityPlayerController::Pressed(const ETouchIndex::Type FingerIndex, FVector Location)
{
	if (bDoOnce == true)
	{
		bIsPressed = true;
		
		touchStart.X = Location.Y;
		touchStart.Y = Location.X;
	}
}

void AParagon_CityPlayerController::Released(const ETouchIndex::Type FingerIndex, FVector Location)
{
	bDoOnce = false;
	bIsPressed = false;
}

void AParagon_CityPlayerController::MoveRightTouch()
{
	if (touchStart.Y - inputVector.X > 20.0f || touchStart.Y - inputVector.X < -20.0f)
	{
		touchEnd.X = inputVector.Y;
		touchEnd.Y = inputVector.X;
		
		if (touchEnd.X < touchStart.X)
		{
			
			finalLocation = UKismetMathLibrary::MakeVector(0, (touchStart.Y - touchEnd.Y) * 0.1f, 0);

			builtManager->CameraBoom->SetWorldLocation(builtManager->CameraBoom->GetComponentLocation() + finalLocation);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *finalLocation.ToString());
		}
	}

}

void AParagon_CityPlayerController::MoveLeftTouch()
{

}







