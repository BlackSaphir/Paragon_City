// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera_Manager.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UnrealClient.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values for this component's properties
UCamera_Manager::UCamera_Manager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	// Create camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create camera
	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}


// Called when the game starts
void UCamera_Manager::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	UserSettings = UGameUserSettings::GetGameUserSettings();

	//Manager = NewObject<ABuilt_Manager>();
}


// Called every frame
void UCamera_Manager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	/*Resolution_X = UserSettings->GetScreenResolution().X;
	Resolution_Y = UserSettings->GetScreenResolution().Y;

	PlayerController->GetMousePosition(Mouseposition_X, Mouseposition_Y);

	UE_LOG(LogTemp, Warning, TEXT("%f"), Mouseposition_X);

	if (Mouseposition_X > Resolution_X / 2 + 50)
	{
		Manager->SetActorLocation(FVector(Mouseposition_X, 0, 0));

		UE_LOG(LogTemp, Warning, TEXT("Penis"));
	}*/
}

void UCamera_Manager::MoveRight(float axisvalue)
{
	float distance = axisvalue * 10.0f;

	FVector rightVector = UKismetMathLibrary::GetRightVector(FRotator(0, 0, 0));

	FVector newLocation = TopDownCamera->GetComponentLocation() + (rightVector * distance);

	TopDownCamera->SetWorldLocation(newLocation);
}

