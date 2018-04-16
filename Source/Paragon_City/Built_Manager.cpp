// Fill out your copyright notice in the Description page of Project Settings.

#include "Built_Manager.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UnrealClient.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ABuilt_Manager::ABuilt_Manager()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create camera
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}

// Called when the game starts or when spawned
void ABuilt_Manager::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

}

// Called every frame
void ABuilt_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();

	Resolution_X = UserSettings->GetScreenResolution().X;
	Resolution_Y = UserSettings->GetScreenResolution().Y;

	PlayerController->GetMousePosition(Mouseposition_X, Mouseposition_Y);

	UE_LOG(LogTemp, Warning, TEXT("%f"), Mouseposition_X);
	if (Mouseposition_X > Resolution_X / 2)
	{
		UE_LOG(LogTemp, Warning, TEXT("Penis"));
	}
}

// Called to bind functionality to input
void ABuilt_Manager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

