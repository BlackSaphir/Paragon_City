// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera_Manager.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values for this component's properties
UCamera_Manager::UCamera_Manager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;


}

void UCamera_Manager::BeginPlay()
{
	Super::BeginPlay();
	//UserSettings = UGameUserSettings::GetGameUserSettings();

}

#if PLATFORM_WINDOWS

void UCamera_Manager::MoveRight(float axisvalue, float Rightspeed, UCameraComponent* Camera_Component)
{

	//UE_LOG(LogTemp, Warning, TEXT("%f"), ResolutionX);

	if (Camera_Component != nullptr)
	{
		if (MousepositionX > ResolutionX / 2 + 100)
		{
			//bLockedX = true;


			float distance = 2 * Rightspeed;

			FVector rightVector = UKismetMathLibrary::GetRightVector(FRotator(0, 0, 0));

			FVector newLocation = Camera_Component->GetComponentLocation() + (rightVector * distance);

			Camera_Component->SetWorldLocation(newLocation);


			UE_LOG(LogTemp, Warning, TEXT("%s"), *Camera_Component->GetComponentLocation().ToString());

			UE_LOG(LogTemp, Warning, TEXT("Rechts Rechts"));
		}
		else
		{
			//bLockedX = false;



			float distance = axisvalue * Rightspeed;

			FVector rightVector = UKismetMathLibrary::GetRightVector(FRotator(0, 0, 0));

			FVector newLocation = Camera_Component->GetComponentLocation() + (rightVector * distance);

			Camera_Component->SetWorldLocation(newLocation);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Camera_Component->GetComponentLocation().ToString());

			UE_LOG(LogTemp, Warning, TEXT("Rechts"));
			UE_LOG(LogTemp, Warning, TEXT("%f"), MousepositionX);
		}

		if (MousepositionX < ResolutionX / 2 - 100)
		{
			float distance = 2 * Rightspeed;

			FVector rightVector = UKismetMathLibrary::GetRightVector(FRotator(0, 0, 0));

			FVector newLocation = Camera_Component->GetComponentLocation() + (rightVector * distance);

			Camera_Component->SetWorldLocation(newLocation);
			UE_LOG(LogTemp, Warning, TEXT("Links"));
		}
		else
		{
			float distance = axisvalue * Rightspeed;

			FVector rightVector = UKismetMathLibrary::GetRightVector(FRotator(0, 0, 0));

			FVector newLocation = Camera_Component->GetComponentLocation() + (rightVector * distance);

			Camera_Component->SetWorldLocation(newLocation);
			UE_LOG(LogTemp, Warning, TEXT("Links Links"));
		}


	}
}


void UCamera_Manager::MoveForward(float axisvalue, float ForwardSpeed, UCameraComponent * Camera_Component)
{
	if (Camera_Component != nullptr)
	{
		float distance = axisvalue * ForwardSpeed;

		FVector rightVector = UKismetMathLibrary::GetForwardVector(FRotator(0, 0, 0));

		FVector newLocation = Camera_Component->GetComponentLocation() + (rightVector * distance);

		Camera_Component->SetWorldLocation(newLocation);
	}
}



#endif


#if PLATFORM_IOS

void UCamera_Manager::MoveRight(float axisvalue, float Rightspeed, UCameraComponent* Camera_Component)
{
	if (Camera_Component != nullptr)
	{
		float distance = axisvalue * Rightspeed;

		FVector rightVector = UKismetMathLibrary::GetRightVector(FRotator(0, 0, 0));

		FVector newLocation = Camera_Component->GetComponentLocation() + (rightVector * distance);

		Camera_Component->SetWorldLocation(newLocation);
	}
}

void UCamera_Manager::MoveForward(float axisvalue, float ForwardSpeed, UCameraComponent * Camera_Component)
{
	if (Camera_Component != nullptr)
	{
		float distance = axisvalue * ForwardSpeed;

		FVector rightVector = UKismetMathLibrary::GetForwardVector(FRotator(0, 0, 0));

		FVector newLocation = Camera_Component->GetComponentLocation() + (rightVector * distance);

		Camera_Component->SetWorldLocation(newLocation);
	}
}

#endif



