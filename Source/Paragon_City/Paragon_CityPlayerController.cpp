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
}

// set InputVector and call MoveRight
void AParagon_CityPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bIsPressed == true)
	{
		// ERROR: bIsCurrentlyPressed always false after first time
		GetInputTouchState(ETouchIndex::Touch1, inputX, InputY, bIsCurrentlyPressed);
		//inputVector = UKismetMathLibrary::MakeVector2D(inputX, InputY);
		inputVector.X = inputX;
		inputVector.Y = InputY;
		UE_LOG(LogTemp, Warning, TEXT("bIsCurrentlyPressed: %s"), (bIsCurrentlyPressed ? TEXT("true") : TEXT("false")));
		UE_LOG(LogTemp, Warning, TEXT("inputVector: %s"), *inputVector.ToString());
		UE_LOG(LogTemp, Warning, TEXT("touchstart: %s"), *touchStart.ToString());
		UE_LOG(LogTemp, Warning, TEXT("touchend: %s"), *touchEnd.ToString());
		MoveRightTouch();
		MoveLeftTouch();
	}
}


bool AParagon_CityPlayerController::InputTouch(uint32 Handle, ETouchType::Type Type, const FVector2D & TouchLocation, FDateTime DeviceTimestamp, uint32 TouchpadIndex)
{
	switch (Type)
	{
	case ETouchType::Began:

		//DeprojectScreenPositionToWorld(TouchLocation.X, TouchLocation.Y, worldLocStart, worldDir);

		// set Touchlocation
		bIsPressed = true;
		bDoOnce = true;
		/*touchStart.X = TouchLocation.Y;
		touchStart.Y = TouchLocation.X;*/

		touchStart.X = TouchLocation.X;
		touchStart.Y = TouchLocation.Y;

		//Pressed(ETouchIndex::Touch1, worldLocStart);
	case ETouchType::Moved:

		UE_LOG(LogTemp, Warning, TEXT("MOVING"));
		touchEnd.X = TouchLocation.X;
		UE_LOG(LogTemp, Warning, TEXT("TouchEndMOVING: %s"), *touchEnd.ToString());
		bIsCurrentlyPressed = true;		
		break;
	case ETouchType::Stationary:
		break;
	case ETouchType::Ended:

		bIsPressed = false;
		bDoOnce = false;
	case ETouchType::NumTypes:
		break;
	default:
		break;
	}


	return false;
}

// not called atm
void AParagon_CityPlayerController::Pressed(const ETouchIndex::Type FingerIndex, FVector Location)
{
	if (bDoOnce == true)
	{
		//touchStart.X = Location.Y;
		//touchStart.Y = Location.X;
		bIsPressed = true;

	}
}

// check if touch goes right
void AParagon_CityPlayerController::MoveRightTouch()
{
	if (touchStart.Y - inputVector.X > 20.0f || touchStart.Y - inputVector.X < -20.0f)
	{
		/*touchEnd.X = inputVector.Y;
		touchEnd.Y = inputVector.X;*/

		if (touchEnd.X > touchStart.X)
		{

			// ERROR? : finalLocation wrong -----> Hast start - end gerechnet
			finalLocation = UKismetMathLibrary::MakeVector((touchEnd.X - touchStart.X)/* * 0.1f*/, 0, 0) /** (-1.0f)*/;

			currentCameraBoomLocation = builtManager->CameraBoom->GetComponentLocation() + finalLocation;
			builtManager->CameraBoom->SetWorldLocation(currentCameraBoomLocation /*builtManager->CameraBoom->GetComponentLocation() + finalLocation*/);
			//builtManager->SetActorLocation(builtManager->GetActorLocation() + finalLocation);
			UE_LOG(LogTemp, Warning, TEXT("finalLocation: %s"), *finalLocation.ToString());
			UE_LOG(LogTemp, Warning, TEXT("cameraBoomLocation: %s"), *currentCameraBoomLocation.ToString() /*builtManager->CameraBoom->GetComponentLocation() + finalLocation).ToString()*/);
		}
	}

}

void AParagon_CityPlayerController::MoveLeftTouch()
{

}







