// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Paragon_CityPlayerController.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"


AParagon_CityPlayerController::AParagon_CityPlayerController(/*const FObjectInitializer & buildManager_Init) :Super(buildManager_Init*/)
{
	bShowMouseCursor = true;
	/*static ConstructorHelpers::FObjectFinder<ABuilt_Manager> buildManager_BP(TEXT("/Game/Blueprints/Character/BP_Built_Manager"));
	builtManager = buildManager_BP.Object;*/
	//Teste das mal ob deine Widgets mit angezeigt werden WTF Was war das? :D lol Ich habe keine Ahnung was das für ein Fehler war
	const ConstructorHelpers::FObjectFinder<UBlueprint> builtManager_BP (TEXT("Blueprint'/Game/Blueprints/Character/BP_Built_Manager.BP_Built_Manager'"));
	if (builtManager_BP.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("Blueprint found"));
		//Könnte zum Crash führen lol :)
		// Ich wollte schon fragen ob das Kunst ist oder weg kann
		//Den Builtmanager musst du jetzt mit dem Pawn ersetzen!
		//Weil wie will man etwas possesen was nicht da ist?
		//Die Engine wird dir da instant Crashen Weil keine World da ist genau! Also alles in BeginPlay Nur das Spawnen jetzt musst du mal google wie du dein Blueprint bzw die Subclass zum instanzieren nutzen kannst
		builtManager = builtManager_BP.Object;
		builtManagerSubClass = builtManager->GeneratedClass;
	}
}


void AParagon_CityPlayerController::BeginPlay()
{
	Super::BeginPlay();
	FTransform CubePlacement(FVector(0, 0, 0));
	FActorSpawnParameters Penis;
	myGameMode = (AParagon_CityGameMode*)GetWorld()->GetAuthGameMode();
	UnPossess();
	//Imo weiß ich auch nicht weiter
	// Probier ich morgen mal weiter. Also irgendwie auf die Built Class kommen oder? Ja du braucht halt die UClass den zu findenden Objekts
	// K mal schauen. Danke dir <3 
	// Immer gern :)
	//Dann ne gute Nacht
	// Dir auch 
	builtManagerPawn = GetWorld()->SpawnActor<ABuilt_Manager>(builtManager->GetBlueprintClass(), CubePlacement, Penis);
	myGameMode->SetDefaultPawnClass(builtManagerSubClass);
	Possess(builtManagerPawn);
}

// set InputVector and call MoveRight
void AParagon_CityPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bIsPressed == true)
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
	switch (Type)
	{
	case ETouchType::Began:
		// set Touchlocation
		bIsPressed = true;
		bDoOnce = true;
		touchStart.X = TouchLocation.X;
		touchStart.Y = TouchLocation.Y;
	case ETouchType::Moved:
		touchEnd.X = TouchLocation.X;
		touchEnd.Y = TouchLocation.Y;
		UE_LOG(LogTemp, Warning, TEXT("Moved"));
		break;
	case ETouchType::Stationary:
		UE_LOG(LogTemp, Warning, TEXT("Stat"));
		break;
	case ETouchType::Ended:
		bIsPressed = false;
		bDoOnce = false;
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









