// Fill out your copyright notice in the Description page of Project Settings.

#include "Built_Manager.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UnrealClient.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/KismetMathLibrary.h"
#include "Paragon_GameInstance.h"



// Sets default values
ABuilt_Manager::ABuilt_Manager()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = DefaultRootComponent;

	// Create camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

										  // Create camera
	//TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	//TopDownCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	//TopDownCamera->RelativeRotation = FRotator(0.f, 0.f, 0.f);
	//TopDownCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

// Called when the game starts or when spawned
void ABuilt_Manager::BeginPlay()
{
	Super::BeginPlay();
	
	
	
}

// Called every frame
void ABuilt_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*RootComponent->SetWorldRotation(FRotator(CameraBoom->GetComponentRotation().Pitch, CameraBoom->GetComponentRotation().Yaw, CameraBoom->GetComponentRotation().Roll));
	UE_LOG(LogTemp, Warning, TEXT("Rotation: %s"), *RootComponent->GetComponentRotation().ToString());*/

}


