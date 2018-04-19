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


	DefaultRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = DefaultRootComponent;


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

// Called when the game starts or when spawned
void ABuilt_Manager::BeginPlay()
{
	Super::BeginPlay();

	Camera_Manager = NewObject<UCamera_Manager>();

	Camera_Manager->UserSettings = UGameUserSettings::GetGameUserSettings();
	Camera_Manager->ResolutionX = Camera_Manager->UserSettings->GetScreenResolution().X;
	Camera_Manager->ResolutionY = Camera_Manager->UserSettings->GetScreenResolution().Y;
	Camera_Manager->PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

}

// Called every frame
void ABuilt_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Camera_Manager->PlayerController->GetMousePosition(Camera_Manager->MousepositionX, Camera_Manager->MousepositionY);
}

// Called to bind functionality to input
void ABuilt_Manager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveRight", this, &ABuilt_Manager::MoveRight);
	InputComponent->BindAxis("MoveForward", this, &ABuilt_Manager::MoveForward);

}

void ABuilt_Manager::MoveRight(float axisvalue)
{
	Camera_Manager->MoveRight(axisvalue, Rightspeed, TopDownCamera);
}

void ABuilt_Manager::MoveForward(float axisvalue)
{
	Camera_Manager->MoveForward(axisvalue, Forwardspeed, TopDownCamera);
}

