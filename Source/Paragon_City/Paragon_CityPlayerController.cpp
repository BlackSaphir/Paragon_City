// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Paragon_CityPlayerController.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/PrimitiveComponent.h"
#include "ARBlueprintLibrary.h"
#include "Widget.h"
#include "AppleARKit/Public/AppleARKitBlueprintLibrary.h"
#include "AppleARKit/Public/AppleARKitAnchor.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"


#define GETENUMSTRING(etype, evalue) ( (FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true) != nullptr) ? FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true)->GetNameStringByIndex((int32)evalue) : FString("Invalid - are you sure enum uses UENUM() macro?") )


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
		builtManager_Class = builtManager_BP.Object;
		builtManagerSubClass = builtManager_Class;
	}

	const ConstructorHelpers::FObjectFinder<UClass> building_Widget_BP(TEXT("Class'/Game/Blueprints/Widgets/W_Buildings.W_Buildings_C'"));
	if (building_Widget_BP.Succeeded())
	{
		built_Widget_Class = building_Widget_BP.Object;
		building_Widget_SubClass = built_Widget_Class;
	}

	const ConstructorHelpers::FObjectFinder<UClass> spawnPlayground_Widget_BP(TEXT("Class'/Game/Blueprints/Widgets/W_SpawnPlayground.W_SpawnPlayground_C'"));
	if (spawnPlayground_Widget_BP.Succeeded())
	{
		spawnPlayground_Widget_Class = spawnPlayground_Widget_BP.Object;
		spawnPlayground_SubClass = spawnPlayground_Widget_Class;
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

	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "AR_Level")
	{
		spawnPlayground_Widget = CreateWidget<UW_SpawnPlayground>(this, spawnPlayground_SubClass.Get());
		spawnPlayground_Widget->AddToViewport();
		spawnPlayground_Widget->Set_PlayerController();
	}
	else
	{
		building_Widget = CreateWidget<UW_Building>(this, building_Widget_SubClass.Get());
		building_Widget->AddToViewport();
		building_Widget->SetBuilt_Manger();
	}
}

// set InputVector and call MoveRight
void AParagon_CityPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);


	if (bIsPressed && !bMovingBuilding && fingerCount == 1)
	{

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


bool AParagon_CityPlayerController::InputTouch(uint32 Handle, ETouchType::Type Type, const FVector2D & TouchLocation, float Force, FDateTime DeviceTimestamp, uint32 TouchpadIndex)
{
	FHitResult hitResult;



	switch (Type)
	{
	case ETouchType::Began:
		// set Touchlocation

		GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, hitResult);

		//UE_LOG(LogTemp, Warning, TEXT("ARHitTestResult: %f"), *GETENUMSTRING("EAppleARKitHitTestResultType", UseEnum));



		fingerCount++;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Penis1")));
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

		gameViewCamera->SetActorLocation(gameViewCamera->GetActorLocation() + (gameViewCamera->GetActorRightVector() * 10));
	}
}

void AParagon_CityPlayerController::MoveLeftTouch()
{
	dist = FVector2D::Distance(FVector2D(touchStart.X, 0), FVector2D(touchEnd.X, 0));
	if (dist > distance && touchEnd.X < touchStart.X)
	{

		gameViewCamera->SetActorLocation(gameViewCamera->GetActorLocation() - (gameViewCamera->GetActorRightVector() * 10));
	}
}

void AParagon_CityPlayerController::MoveUpTouch()
{
	dist = FVector2D::Distance(FVector2D(0, touchStart.Y), FVector2D(0, touchEnd.Y));

	if (dist > distance && touchEnd.Y < touchStart.Y)
	{


		angleDiff = 360 + gameViewCamera->GetActorRotation().Pitch;
		ForwardVectorManipulated = UKismetMathLibrary::RotateAngleAxis(gameViewCamera->GetActorForwardVector(), angleDiff, FVector(0, 1, 0));
		gameViewCamera->SetActorLocation(gameViewCamera->GetActorLocation() + (ForwardVectorManipulated * 10));
	}
}

void AParagon_CityPlayerController::MoveDownTouch()
{
	dist = FVector2D::Distance(FVector2D(0, touchStart.Y), FVector2D(0, touchEnd.Y));

	if (dist > distance && touchEnd.Y > touchStart.Y)
	{

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
		gameViewCamera->SetActorRelativeLocation(gameViewCamera->GetActorLocation() + touchDIr * speedMultiplier);
	}
}


void AParagon_CityPlayerController::SpawnARFloor()
{
	FActorSpawnParameters spawnParamFloor;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(UARBlueprintLibrary::GetAllGeometries().Max()));

	plane = Cast<UARPlaneGeometry>(UARBlueprintLibrary::GetAllGeometries().Top());
	
	
	if (plane)
	{
		spawnLocation_Playground.X = plane->GetCenter().X;
		spawnLocation_Playground.Y = plane->GetCenter().Y;
		spawnLocation_Playground.Z = plane->GetCenter().Z;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("plane not null")));
		GetWorld()->SpawnActor<AActor>(builtManagerPawn->Floor, FVector(spawnLocation_Playground.X, spawnLocation_Playground.Y, spawnLocation_Playground.Z), FRotator(0, 0, -45), spawnParamFloor);
	}

	UARBlueprintLibrary::PauseARSession();
	
	/*spawnPlayground_Widget->RemoveFromParent();
	building_Widget = CreateWidget<UW_Building>(this, building_Widget_SubClass.Get());
	building_Widget->AddToViewport();
	building_Widget->SetBuilt_Manger();*/
}













