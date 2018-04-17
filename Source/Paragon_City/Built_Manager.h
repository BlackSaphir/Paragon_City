// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera_Manager.h"
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

	UPROPERTY(EditAnywhere)
		class USceneComponent* DefaultRootComponent;

	// Function

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UFUNCTION()
		void MoveRight(float axisvalue);


	// Variable

private:

	UCamera_Manager* Camera_Manager;


};
