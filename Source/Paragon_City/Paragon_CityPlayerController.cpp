// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Paragon_CityPlayerController.h"
#include "Runtime/AppleARKit/Source/AppleARKit/Public/AppleARKitCamera.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/PrimitiveComponent.h"



AParagon_CityPlayerController::AParagon_CityPlayerController(/*const FObjectInitializer & buildManager_Init) :Super(buildManager_Init*/)
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	bEnableMouseOverEvents = true;
	bEnableTouchOverEvents = true;
	bBlockInput = false;
	bAutoManageActiveCameraTarget = false;
	
	//PlayerCameraManager = nullptr;

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
	FTransform cubePlacement(FVector(0, 0, 0));
	FActorSpawnParameters spawnParas;
	myGameMode = (AParagon_CityGameMode*)GetWorld()->GetAuthGameMode();
	defaultPawn = GetPawn();
	UnPossess();
	builtManagerPawn = GetWorld()->SpawnActor<ABuilt_Manager>(builtManagerSubClass, cubePlacement, spawnParas);
	myGameMode->SetDefaultPawnClass(builtManagerSubClass);
	Possess(builtManagerPawn);
	defaultPawn->Destroy();
	builtManagerPawn->SecondBeginPlay();
	gameViewCamera = NewObject<AGameView_Camera>();
	FActorSpawnParameters SpawnParam;
	gameViewCamera = GetWorld()->SpawnActor<AGameView_Camera>(gameViewCamera->GetClass(), FVector(0, 0, 900), FRotator(300, 0, 0), SpawnParam);
	SetViewTarget(gameViewCamera);

	FAppleARKitCamera();
}

// set InputVector and call MoveRight
void AParagon_CityPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	//builtManagerPawn->SetActorRotation(builtManagerPawn->TopDownCamera->GetComponentRotation());
	//UE_LOG(LogTemp, Warning, TEXT("%d"), fingerCount);
	if (bIsPressed && !bMovingBuilding && fingerCount == 1)
	{
		//GetInputTouchState(ETouchIndex::Touch1, inputX, InputY, bIsCurrentlyPressed);
		//inputVector.X = inputX;
		//inputVector.Y = InputY;
		MoveRightTouch();
		MoveLeftTouch();
		MoveUpTouch();
		MoveDownTouch();

		//Move();

	}

	if (fingerCount == 2 && !bMovingBuilding)
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
		//builtManagerPawn->SetActorRotation(builtManagerPawn->CameraBoom->GetComponentRotation());
		//UE_LOG(LogTemp, Warning, TEXT("öcyvksdnjdökjf: %s"), *builtManagerPawn->GetActorRotation().ToString());
		GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, hitResult);
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
			}
			else
			{
				bIsPressed = true;
				touchStart.X = TouchLocation.X;
				touchStart.Y = TouchLocation.Y;
			}
		}
	case ETouchType::Moved:
		DeprojectScreenPositionToWorld(screenX, screenY, worldLoc, worldDir);
		//UE_LOG(LogTemp, Warning, TEXT("World Dir: %s"), *worldDir.ToString());
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
	dist = FVector2D::Distance(FVector2D(touchStart.X, 0), FVector2D(touchEnd.X, 0));
	if (dist > distance && touchEnd.X > touchStart.X)
	{
		/*finalLocation = UKismetMathLibrary::MakeVector2D(0, ((touchEnd.X - touchStart.X) * speedMultiplier));
		builtManagerPawn->SetActorRelativeLocation(FVector(builtManagerPawn->GetActorLocation().X + finalLocation.X, builtManagerPawn->GetActorLocation().Y + finalLocation.Y, builtManagerPawn->GetActorLocation().Z));*/
		//builtManagerPawn->SetActorRelativeLocation(FVector(builtManagerPawn->GetActorLocation().X, builtManagerPawn->GetActorLocation().Y * builtManagerPawn->GetActorForwardVector().Y + 10, builtManagerPawn->GetActorLocation().Z));
		/*UE_LOG(LogTemp, Warning, TEXT("Right Vector: %s"), *builtManagerPawn->GetActorRightVector().ToString());*/
		gameViewCamera->SetActorLocation(gameViewCamera->GetActorLocation() + (gameViewCamera->GetActorRightVector() * 10));
	}
}

void AParagon_CityPlayerController::MoveLeftTouch()
{
	dist = FVector2D::Distance(FVector2D(touchStart.X, 0), FVector2D(touchEnd.X, 0));
	if (dist > distance && touchEnd.X < touchStart.X)
	{
		/*finalLocation = UKismetMathLibrary::MakeVector2D(0, (touchEnd.X - touchStart.X) * speedMultiplier);
		builtManagerPawn->SetActorRelativeLocation(FVector(builtManagerPawn->GetActorLocation().X + finalLocation.X, builtManagerPawn->GetActorLocation().Y + finalLocation.Y, builtManagerPawn->GetActorLocation().Z));*/
		//builtManagerPawn->SetActorRelativeLocation(FVector(builtManagerPawn->GetActorLocation().X, builtManagerPawn->GetActorLocation().Y * builtManagerPawn->GetActorForwardVector().Y - 10, builtManagerPawn->GetActorLocation().Z));
		gameViewCamera->SetActorLocation(gameViewCamera->GetActorLocation() - (gameViewCamera->GetActorRightVector() * 10));
	}
}

void AParagon_CityPlayerController::MoveUpTouch()
{
	dist = FVector2D::Distance(FVector2D(0, touchStart.Y), FVector2D(0, touchEnd.Y));

	if (dist > distance && touchEnd.Y < touchStart.Y)
	{
		/*finalLocation = UKismetMathLibrary::MakeVector2D((touchStart.Y - touchEnd.Y)* speedMultiplier, 0);
		builtManagerPawn->SetActorRelativeLocation(FVector(builtManagerPawn->GetActorLocation().X + finalLocation.X, builtManagerPawn->GetActorLocation().Y + finalLocation.Y, builtManagerPawn->GetActorLocation().Z));*/
		//builtManagerPawn->SetActorRelativeLocation(FVector(builtManagerPawn->GetActorLocation().X * builtManagerPawn->GetActorForwardVector().Y + 10, builtManagerPawn->GetActorLocation().Y, builtManagerPawn->GetActorLocation().Z));
		//UE_LOG(LogTemp, Warning, TEXT("forward Vector: %s"), *builtManagerPawn->GetActorForwardVector().ToString());

		angleDiff = 360 + gameViewCamera->GetActorRotation().Pitch;
		ForwardVectorManipulated = UKismetMathLibrary::RotateAngleAxis(gameViewCamera->GetActorForwardVector(), angleDiff, FVector(0, 1, 0));
		gameViewCamera->SetActorLocation(gameViewCamera->GetActorLocation() + (ForwardVectorManipulated * 10));
		UE_LOG(LogTemp, Warning, TEXT("Pitch: %f"), gameViewCamera->GetActorRotation().Pitch);
	}
}

void AParagon_CityPlayerController::MoveDownTouch()
{
	dist = FVector2D::Distance(FVector2D(0, touchStart.Y), FVector2D(0, touchEnd.Y));

	if (dist > distance && touchEnd.Y > touchStart.Y)
	{
		/*finalLocation = UKismetMathLibrary::MakeVector2D((touchStart.Y - touchEnd.Y)* speedMultiplier, 0);
		builtManagerPawn->SetActorRelativeLocation(FVector(builtManagerPawn->GetActorLocation().X + finalLocation.X, builtManagerPawn->GetActorLocation().Y + finalLocation.Y, builtManagerPawn->GetActorLocation().Z));*/
		//builtManagerPawn->SetActorRelativeLocation(FVector(builtManagerPawn->GetActorLocation().X * builtManagerPawn->GetActorForwardVector().Y - 10, builtManagerPawn->GetActorLocation().Y, builtManagerPawn->GetActorLocation().Z));

		angleDiff = 360 + gameViewCamera->GetActorRotation().Pitch;
		ForwardVectorManipulated = UKismetMathLibrary::RotateAngleAxis(gameViewCamera->GetActorForwardVector(), angleDiff, FVector(0, 1, 0));
		gameViewCamera->SetActorLocation(gameViewCamera->GetActorLocation() - (ForwardVectorManipulated * 10));
	}
}

void AParagon_CityPlayerController::Zoom()
{
	/*float dist1 = FVector2D::Distance(secondFingerTouchStart, firstFingerTouchStart);
	float dist2 = FVector2D::Distance(secondFingerTouchEnd, firstFingerTouchEnd);
	float deltaDistance = dist2 - dist1;
	if (deltaDistance > 25)
	{
		if (builtManagerPawn->CameraBoom->TargetArmLength > 600.0f)
		{
			builtManagerPawn->CameraBoom->TargetArmLength = builtManagerPawn->CameraBoom->TargetArmLength - 10.0f;
		}
	}
	else if (deltaDistance < -25)
	{
		if (builtManagerPawn->CameraBoom->TargetArmLength < 3000.0f)
		{
			builtManagerPawn->CameraBoom->TargetArmLength = builtManagerPawn->CameraBoom->TargetArmLength + 10.0f;
		}
	}*/
}

void AParagon_CityPlayerController::Move()
{
	dist = FVector2D::Distance(touchStart, touchEnd);

	touchDIr = FVector((touchEnd.Y - touchStart.Y)*(-1), touchEnd.X - touchStart.X, 0);

	if (dist > distance)
	{
		gameViewCamera->SetActorRelativeLocation(gameViewCamera->GetActorLocation() + touchDIr*speedMultiplier);
	}
}









