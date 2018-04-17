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

}

// Called when the game starts or when spawned
void ABuilt_Manager::BeginPlay()
{
	Super::BeginPlay();

	Camera_Manager = NewObject<UCamera_Manager>();

}

// Called every frame
void ABuilt_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

// Called to bind functionality to input
void ABuilt_Manager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveRight", this, &ABuilt_Manager::MoveRight);

}

void ABuilt_Manager::MoveRight(float axisvalue)
{
	float distance = axisvalue * 10.0f;

	FVector rightVector = UKismetMathLibrary::GetRightVector(FRotator(0, 0, 0));

	FVector newLocation = GetActorLocation() + (rightVector * distance);

	SetActorLocation(newLocation);


	//Camera_Manager->MoveRight(axisvalue);
}

