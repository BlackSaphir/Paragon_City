// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Paragon_CityPlayerController.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/PrimitiveComponent.h"



AParagon_CityPlayerController::AParagon_CityPlayerController(/*const FObjectInitializer & buildManager_Init) :Super(buildManager_Init*/)
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	bEnableMouseOverEvents = true;
	bEnableTouchOverEvents = true;
	bBlockInput = false;

	const ConstructorHelpers::FObjectFinder<UClass> builtManager_BP(TEXT("Class'/Game/Blueprints/Character/BP_Built_Manager.BP_Built_Manager_C'"));
	if (builtManager_BP.Succeeded())
	{
		builtManager = builtManager_BP.Object;
		builtManagerSubClass = builtManager;
	}
}


void AParagon_CityPlayerController::BeginPlay()
{
	Super::BeginPlay();
	FTransform CubePlacement(FVector(0, 0, 0));
	FActorSpawnParameters Penis;
	myGameMode = (AParagon_CityGameMode*)GetWorld()->GetAuthGameMode();
	defaultPawn = GetPawn();
	UnPossess();
	builtManagerPawn = GetWorld()->SpawnActor<ABuilt_Manager>(builtManagerSubClass, CubePlacement, Penis);
	myGameMode->SetDefaultPawnClass(builtManagerSubClass);
	Possess(builtManagerPawn);
	defaultPawn->Destroy();
	builtManagerPawn->SecondBeginPlay();
}

// set InputVector and call MoveRight
void AParagon_CityPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("%d"), fingerCount);
	if (bIsPressed && !bMovingBuilding && fingerCount == 1)
	{
		GetInputTouchState(ETouchIndex::Touch1, inputX, InputY, bIsCurrentlyPressed);
		inputVector.X = inputX;
		inputVector.Y = InputY;
		MoveRightTouch();
		MoveLeftTouch();
		MoveUpTouch();
		MoveDownTouch();
	}

	if (fingerCount == 2)
	{
		Zoom();
	}
}


bool AParagon_CityPlayerController::InputTouch(uint32 Handle, ETouchType::Type Type, const FVector2D & TouchLocation, FDateTime DeviceTimestamp, uint32 TouchpadIndex)
{
	FHitResult hitResult;

	switch (Type)
	{
	case ETouchType::Began:
		// set Touchlocation
		GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, hitResult);
		//UE_LOG(LogTemp, Warning, TEXT("FingerIndex: %d"), Handle);
		fingerCount++;

		if (fingerCount == 1)
		{
			firstFingerTouchStart = TouchLocation;
		}
		else if (fingerCount == 2)
		{
			secondFingerTouchStart = TouchLocation;
		}
		if (hitResult.GetActor() != NULL)
		{
			if (hitResult.GetActor()->ActorHasTag("Building"))
			{
				primitive_Comp = hitResult.GetComponent();
				primitive_Comp->DispatchOnInputTouchBegin(ETouchIndex::Touch1);
				UE_LOG(LogTemp, Warning, TEXT("Deine Mama"));
			}
			else
			{
				bIsPressed = true;
				touchStart.X = TouchLocation.X;
				touchStart.Y = TouchLocation.Y;
			}
		}
	case ETouchType::Moved:

		if (Handle == 0)
		{
			firstFingerTouchEnd = TouchLocation;
		}
		if (Handle == 1)
		{
			secondFingerTouchEnd = TouchLocation;
		}
		touchEnd.X = TouchLocation.X;
		touchEnd.Y = TouchLocation.Y;
		break;
	case ETouchType::Stationary:
		break;
	case ETouchType::Ended:
		fingerCount--;
		if (primitive_Comp != nullptr)
		{
			primitive_Comp->DispatchOnInputTouchEnd(ETouchIndex::Touch1);
		}
		bIsPressed = false;
		break;
	case ETouchType::NumTypes:
		break;
	default:
		break;
	}

	return false;
}


// check if touch goes right
void AParagon_CityPlayerController::MoveRightTouch()
{

	float dist = FVector2D::Distance(FVector2D(touchStart.X, 0), FVector2D(touchEnd.X, 0));

	if (dist > distance && touchEnd.X > touchStart.X)
	{
		finalLocation = UKismetMathLibrary::MakeVector2D(0, ((touchEnd.X - touchStart.X) * speedMultiplier));
		builtManagerPawn->SetActorLocation(FVector(builtManagerPawn->GetActorLocation().X + finalLocation.X, builtManagerPawn->GetActorLocation().Y + finalLocation.Y, builtManagerPawn->GetActorLocation().Z));
	}
}

void AParagon_CityPlayerController::MoveLeftTouch()
{
	float dist = FVector2D::Distance(FVector2D(touchStart.X, 0), FVector2D(touchEnd.X, 0));

	if (dist > distance && touchEnd.X < touchStart.X)
	{
		finalLocation = UKismetMathLibrary::MakeVector2D(0, (touchEnd.X - touchStart.X) * speedMultiplier);
		builtManagerPawn->SetActorLocation(FVector(builtManagerPawn->GetActorLocation().X + finalLocation.X, builtManagerPawn->GetActorLocation().Y + finalLocation.Y, builtManagerPawn->GetActorLocation().Z));
	}
}

void AParagon_CityPlayerController::MoveUpTouch()
{
	float dist = FVector2D::Distance(FVector2D(0, touchStart.Y), FVector2D(0, touchEnd.Y));

	if (dist > distance && touchEnd.Y < touchStart.Y)
	{
		finalLocation = UKismetMathLibrary::MakeVector2D((touchStart.Y - touchEnd.Y)* speedMultiplier, 0);
		builtManagerPawn->SetActorLocation(FVector(builtManagerPawn->GetActorLocation().X + finalLocation.X, builtManagerPawn->GetActorLocation().Y + finalLocation.Y, builtManagerPawn->GetActorLocation().Z));
	}
}

void AParagon_CityPlayerController::MoveDownTouch()
{
	float dist = FVector2D::Distance(FVector2D(0, touchStart.Y), FVector2D(0, touchEnd.Y));

	if (dist > distance && touchEnd.Y > touchStart.Y)
	{
		finalLocation = UKismetMathLibrary::MakeVector2D((touchStart.Y - touchEnd.Y)* speedMultiplier, 0);
		builtManagerPawn->SetActorLocation(FVector(builtManagerPawn->GetActorLocation().X + finalLocation.X, builtManagerPawn->GetActorLocation().Y + finalLocation.Y, builtManagerPawn->GetActorLocation().Z));
	}
}

void AParagon_CityPlayerController::Zoom()
{
	FVector worldLoc;
	FVector worldDir = builtManagerPawn->GetActorForwardVector();
	float dist1 = FVector2D::Distance(secondFingerTouchStart, firstFingerTouchStart);
	float dist2 = FVector2D::Distance(secondFingerTouchEnd, firstFingerTouchEnd);
	float deltaDistance = dist2 - dist1;
	FVector2D center = FVector2D(0.5f*(firstFingerTouchEnd.X + secondFingerTouchEnd.X), 0.5f*(firstFingerTouchEnd.Y + secondFingerTouchEnd.Y));
	DeprojectScreenPositionToWorld(center.X, center.Y, worldLoc, worldDir);
	if (deltaDistance > 25)
	{
		//builtManagerPawn->SetActorLocation(FVector(FMath::Lerp(  builtManagerPawn->GetActorLocation().X, worldLoc.X, 0.1f), FMath::Lerp(builtManagerPawn->GetActorLocation().Y, worldLoc.Y, 0.1f), builtManagerPawn->GetActorLocation().Z - 10.0f));
		//builtManagerPawn->SetActorLocation(FVector(builtManagerPawn->GetActorLocation().X,builtManagerPawn->GetActorLocation().Y, builtManagerPawn->GetActorLocation().Z - 10.0f));
		builtManagerPawn->SetActorLocation(FVector(worldLoc.X, worldLoc.Y, builtManagerPawn->GetActorLocation().Z - 10.0f));

		UE_LOG(LogTemp, Warning, TEXT("ScreenLoc: %s"), *center.ToString());
		UE_LOG(LogTemp, Warning, TEXT("WorldLoc: %s"), *worldLoc.ToString());

	}
	else if (deltaDistance < -25)
	{
		UE_LOG(LogTemp, Warning, TEXT("ScreenLoc: %s"), *center.ToString());
		UE_LOG(LogTemp, Warning, TEXT("WorldLoc: %s"), *worldLoc.ToString());
		//builtManagerPawn->SetActorLocation(FVector(FMath::Lerp(builtManagerPawn->GetActorLocation().X, worldLoc.X, 0.1f), FMath::Lerp( builtManagerPawn->GetActorLocation().Y, worldLoc.Y, 0.1f), builtManagerPawn->GetActorLocation().Z + 10.0f));
		//builtManagerPawn->SetActorLocation(FVector(builtManagerPawn->GetActorLocation().X, builtManagerPawn->GetActorLocation().Y, builtManagerPawn->GetActorLocation().Z + 10.0f));
		builtManagerPawn->SetActorLocation(FVector(worldLoc.X,  worldLoc.Y, builtManagerPawn->GetActorLocation().Z + 10.0f));

	}
}









