// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraActor.h"
#include "Built_Manager.generated.h"

UCLASS()
class PARAGON_CITY_API ABuilt_Manager : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABuilt_Manager();

	// Component

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USceneComponent* DefaultRootComponent;

	UFUNCTION(BlueprintImplementableEvent)
		void SecondBeginPlay();

	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* TopDownCamera;*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;


	// Function

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
private:
	void SpawnCamera();
	
	// Variable
private:
	
};
