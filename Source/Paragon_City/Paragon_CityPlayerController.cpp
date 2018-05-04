// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Paragon_CityPlayerController.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"

AParagon_CityPlayerController::AParagon_CityPlayerController()
{
	bShowMouseCursor = true;
	BuiltManager = NewObject<ABuilt_Manager>();
}

void AParagon_CityPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);


}

void AParagon_CityPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();



	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AParagon_CityPlayerController::MoveRightTouch);

}

bool AParagon_CityPlayerController::InputTouch(uint32 Handle, ETouchType::Type Type, const FVector2D & TouchLocation, FDateTime DeviceTimestamp, uint32 TouchpadIndex)
{
	switch (Type)
	{
	case ETouchType::Began:
		break;
	case ETouchType::Moved:
		break;
		//MoveRightTouch(ETouchIndex::Touch1, FVector(TouchLocation.X, TouchLocation.Y, 1.0f));
	case ETouchType::Stationary:
		break;
	case ETouchType::Ended:
		break;
	case ETouchType::NumTypes:
		break;
	default:
		break;
	}


	return false;
}



void AParagon_CityPlayerController::MoveRightTouch(const ETouchIndex::Type FingerIndex,  FVector Location)
{
	

	float distance = 2 * 1;

	FVector rightVector = UKismetMathLibrary::GetRightVector(FRotator(0, 0, 0));

	FVector newLocation = BuiltManager->GetTargetLocation() + (rightVector * distance);

	BuiltManager->SetActorLocation(newLocation);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *BuiltManager->GetTargetLocation().ToString());

	UE_LOG(LogTemp, Warning, TEXT("Moved"));
}






