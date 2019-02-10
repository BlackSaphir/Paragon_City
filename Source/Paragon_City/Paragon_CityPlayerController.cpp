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
#include "W_AR.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"


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
	PrimaryActorTick.bTickEvenWhenPaused = true;


	//PlayerCameraManager = nullptr;

	const ConstructorHelpers::FObjectFinder<UClass> builtManager_BP(TEXT("Class'/Game/Blueprints/Character/BP_Built_Manager.BP_Built_Manager_C'"));
	if (builtManager_BP.Succeeded())
	{
		builtManager_Class = builtManager_BP.Object;
		builtManagerSubClass = builtManager_Class;
	}

	const ConstructorHelpers::FObjectFinder<UClass> building_Widget_BP(TEXT("Class'/Game/Blueprints/Widgets/W_Buildings_Right.W_Buildings_Right_C'"));
	if (building_Widget_BP.Succeeded())
	{
		built_Widget_Class = building_Widget_BP.Object;
		building_Widget_SubClass = built_Widget_Class;
	}

	const ConstructorHelpers::FObjectFinder<UClass>AR_Widget_BP(TEXT("Class'/Game/Blueprints/Widgets/W_AR_Right.W_AR_Right_C'"));
	if (AR_Widget_BP.Succeeded())
	{
		AR_Widget_Class = AR_Widget_BP.Object;
		AR_Widget_SubClass = AR_Widget_Class;
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
	world = GetWorld();
	myGameMode = (AParagon_CityGameMode*)GetWorld()->GetAuthGameMode();
	defaultPawn = GetPawn();
	UnPossess();
	BuiltManagerPawn = GetWorld()->SpawnActor<ABuilt_Manager>(builtManagerSubClass, cubePlacement, spawnParas);
	myGameMode->SetDefaultPawnClass(builtManagerSubClass);
	Possess(BuiltManagerPawn);
	defaultPawn->Destroy();
	BuiltManagerPawn->SecondBeginPlay();
	gameViewCamera = NewObject<AGameView_Camera>();
	FActorSpawnParameters SpawnParam;
	gameViewCamera = GetWorld()->SpawnActor<AGameView_Camera>(gameViewCamera->GetClass(), FVector(0, 0, 900), FRotator(285, 0, 0), SpawnParam);
	SetViewTarget(gameViewCamera);
	

	UW_AR* AR_Widget;
	


	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "AR_Level")
	{
		spawnPlayground_Widget = CreateWidget<UW_SpawnPlayground>(this, spawnPlayground_SubClass.Get());
		spawnPlayground_Widget->AddToViewport();
		spawnPlayground_Widget->Set_PlayerController();
		bIsARSession = true;
	}
	else
	{
		building_Widget = CreateWidget<UW_Building>(this, building_Widget_SubClass.Get());
		building_Widget->AddToViewport();
		building_Widget->SetBuilt_Manger();
	}

	if (myGameMode->support_AR == true)
	{
		AR_Widget = CreateWidget<UW_AR>(this, AR_Widget_SubClass.Get());
		AR_Widget->AddToViewport();
		AR_Widget->SetBuilt_Manger();
	}


}

// set InputVector and call MoveRight
void AParagon_CityPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);


	if (bIsPressed && !bMovingBuilding && fingerCount == 1 && !bIsARSession)
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

bool AParagon_CityPlayerController::LineTrace(UWorld* World, const FVector&Start, const FVector&End, TArray<FHitResult>& HitOut, ECollisionChannel CollisionChannel = ECC_Pawn, bool ReturnPhysMat = false)
{
	if (!World)
	{
		return false;
	}

	FCollisionQueryParams TraceParams(FName(TEXT("LineTrace")), true);
	TraceParams.bTraceComplex = true;
	TraceParams.bReturnPhysicalMaterial = ReturnPhysMat;


	//Trace
	World->LineTraceMultiByChannel(HitOut, Start, End, CollisionChannel, TraceParams);


	return (&HitOut.Last() != NULL);
}


bool AParagon_CityPlayerController::InputTouch(uint32 Handle, ETouchType::Type Type, const FVector2D & TouchLocation, float Force, FDateTime DeviceTimestamp, uint32 TouchpadIndex)
{
	FString lastHitResult;
	FHitResult hitResult_Touch;
	FHitResult hitResult_LineTrace;

	switch (Type)
	{
	case ETouchType::Began:
		// set Touchlocation

		GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, hitResult_Touch);

		//UE_LOG(LogTemp, Warning, TEXT("ARHitTestResult: %f"), *GETENUMSTRING("EAppleARKitHitTestResultType", UseEnum));



		fingerCount++;
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Penis1")));
		if (fingerCount == 1)
		{
			firstFingerTouchStart = TouchLocation;
		}
		else if (fingerCount == 2)
		{
			secondFingerTouchStart = TouchLocation;
		}
		if (hitResult_Touch.GetActor() != NULL)
		{
			/*if (hitResult_Touch.GetActor()->ActorHasTag("Floor"))
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Floor")));
			}*/

			if (hitResult_Touch.GetActor()->ActorHasTag("Building"))
			{
				primitive_Comp = hitResult_Touch.GetComponent();
				primitive_Comp->DispatchOnInputTouchBegin(ETouchIndex::Touch1);


				LineTrace(world, FVector(primitive_Comp->GetComponentLocation().X, primitive_Comp->GetComponentLocation().Y, primitive_Comp->GetComponentLocation().Z + 50), FVector(primitive_Comp->GetComponentLocation().X, primitive_Comp->GetComponentLocation().Y, primitive_Comp->GetComponentLocation().Z - 500), hitResult_Building, collisionChannel, false);
				DrawDebugLine(world, primitive_Comp->GetComponentLocation(), FVector(primitive_Comp->GetComponentLocation().X, primitive_Comp->GetComponentLocation().Y, primitive_Comp->GetComponentLocation().Z - 500), FColor::Green, true, 5, 0, 2.f);

				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Building Grab")));
				//FString PenisNamePenis = hitResult_Building.Last().GetActor()->GetName();
				//UE_LOG(LogTemp, Warning, TEXT("MyCharacter's Name is %s"), PenisNamePenis);

				if (hitResult_Building.Last().GetActor()->ActorHasTag("Floor"))
				{

					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Floor under Building")));

				}
			}
			else
			{
				touchStart.X = TouchLocation.X;
				touchStart.Y = TouchLocation.Y;
				touchEnd.X = TouchLocation.X;
				touchEnd.Y = TouchLocation.Y;
				bIsPressed = true;
			}
		}
		break;
	case ETouchType::Moved:
		if (bMovingBuilding)
		{
			bStartMoveBuilding = true;
			primitive_Comp->DispatchOnInputTouchBegin(ETouchIndex::Touch1);

			LineTrace(world, FVector(primitive_Comp->GetComponentLocation().X, primitive_Comp->GetComponentLocation().Y, primitive_Comp->GetComponentLocation().Z + 50), FVector(primitive_Comp->GetComponentLocation().X, primitive_Comp->GetComponentLocation().Y, primitive_Comp->GetComponentLocation().Z - 500), hitResult_Building, collisionChannel, false);
			lastHitResult = hitResult_Building.Last().ToString();
			UE_LOG(LogTemp, Warning, TEXT("%s"), *lastHitResult);

			DrawDebugLine(world, FVector(primitive_Comp->GetComponentLocation().X, primitive_Comp->GetComponentLocation().Y, primitive_Comp->GetComponentLocation().Z + 50), FVector(primitive_Comp->GetComponentLocation().X, primitive_Comp->GetComponentLocation().Y, primitive_Comp->GetComponentLocation().Z - 500), FColor::Green, true, 5, 0, 2.f);
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
			bStartMoveBuilding = false;
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



void AParagon_CityPlayerController::CreateBuildingWidget()
{
	//spawnPlayground_Widget->RemoveFromParent();
	//UARBlueprintLibrary::PauseARSession();
	building_Widget = CreateWidget<UW_Building>(this, building_Widget_SubClass.Get());
	building_Widget->AddToViewport();
	building_Widget->SetBuilt_Manger();
}

void AParagon_CityPlayerController::RemoveFloorWidget()
{
	spawnPlayground_Widget->RemoveFromViewport();
}















