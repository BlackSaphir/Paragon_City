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

	if (bIsPressed && !bMovingBuilding)
	{
		GetInputTouchState(ETouchIndex::Touch1, inputX, InputY, bIsCurrentlyPressed);
		inputVector.X = inputX;
		inputVector.Y = InputY;
		MoveRightTouch();
		MoveLeftTouch();
		MoveUpTouch();
		MoveDownTouch();

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

		if (hitResult.GetActor()->ActorHasTag("Building"))
		{
			primitive_Comp = hitResult.GetComponent();
			primitive_Comp->DispatchOnInputTouchBegin(ETouchIndex::Touch1);
			UE_LOG(LogTemp, Warning, TEXT("Deine Mama"));
		}
		else
		{
			bIsPressed = true;
			UE_LOG(LogTemp, Warning, TEXT("FingerIndex: %d"), Handle);
			touchStart.X = TouchLocation.X;
			touchStart.Y = TouchLocation.Y;
		}
	case ETouchType::Moved:
		touchEnd.X = TouchLocation.X;
		touchEnd.Y = TouchLocation.Y;
		break;
	case ETouchType::Stationary:
		break;
	case ETouchType::Ended:
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
		builtManagerPawn->SetActorLocation(FVector(builtManagerPawn->GetActorLocation().X + finalLocation.X, builtManagerPawn->GetActorLocation().Y + finalLocation.Y, 0));
	}
}

void AParagon_CityPlayerController::MoveLeftTouch()
{
	float dist = FVector2D::Distance(FVector2D(touchStart.X, 0), FVector2D(touchEnd.X, 0));

	if (dist > distance && touchEnd.X < touchStart.X)
	{
		finalLocation = UKismetMathLibrary::MakeVector2D(0, (touchEnd.X - touchStart.X) * speedMultiplier);
		builtManagerPawn->SetActorLocation(FVector(builtManagerPawn->GetActorLocation().X + finalLocation.X, builtManagerPawn->GetActorLocation().Y + finalLocation.Y, 0));
	}
}

void AParagon_CityPlayerController::MoveUpTouch()
{
	float dist = FVector2D::Distance(FVector2D(0, touchStart.Y), FVector2D(0, touchEnd.Y));

	if (dist > distance && touchEnd.Y < touchStart.Y)
	{
		finalLocation = UKismetMathLibrary::MakeVector2D((touchStart.Y - touchEnd.Y)* speedMultiplier, 0);
		builtManagerPawn->SetActorLocation(FVector(builtManagerPawn->GetActorLocation().X + finalLocation.X, builtManagerPawn->GetActorLocation().Y + finalLocation.Y, 0));
	}
}

void AParagon_CityPlayerController::MoveDownTouch()
{
	float dist = FVector2D::Distance(FVector2D(0, touchStart.Y), FVector2D(0, touchEnd.Y));

	if (dist > distance && touchEnd.Y > touchStart.Y)
	{
		finalLocation = UKismetMathLibrary::MakeVector2D((touchStart.Y - touchEnd.Y)* speedMultiplier, 0);
		builtManagerPawn->SetActorLocation(FVector(builtManagerPawn->GetActorLocation().X + finalLocation.X, builtManagerPawn->GetActorLocation().Y + finalLocation.Y, 0));
	}
}









