// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Paragon_CityPlayerController.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"

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
	//InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AParagon_CityPlayerController::MoveRightTouch);

}

//bool AParagon_CityPlayerController::InputTouch(uint32 Handle, ETouchType::Type Type, const FVector2D & TouchLocation, FDateTime DeviceTimestamp, uint32 TouchpadIndex)
//{
//	switch (Type)
//	{
//	case ETouchType::Began:
//		break;
//	case ETouchType::Moved:
//		//DeprojectScreenPositionToWorld(TouchLocation.X, TouchLocation.Y, WorldLoc, WorldDir);
//
//		//MoveRightTouch(ETouchIndex::Touch1, WorldLoc);
//	case ETouchType::Stationary:
//		break;
//	case ETouchType::Ended:
//		break;
//	case ETouchType::NumTypes:
//		break;
//	default:
//		break;
//	}
//
//
//	return false;
//}



void AParagon_CityPlayerController::MoveRightTouch(const ETouchIndex::Type FingerIndex,  FVector Location)
{

	float distance = 2 * 1;

	FVector rightVector = UKismetMathLibrary::GetRightVector(FRotator(0, 0, 0));

	FVector newLocation = Location;

	BuiltManager->SetActorRelativeLocation(Location);

	UE_LOG(LogTemp, Warning, TEXT(" Built_Manager_Loc %s"), *BuiltManager->GetTargetLocation().ToString());
	UE_LOG(LogTemp, Warning, TEXT(" Touch Location %s"), *Location.ToString());


	UE_LOG(LogTemp, Warning, TEXT("Moved"));
}






