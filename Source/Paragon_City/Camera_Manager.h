// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera_Manager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PARAGON_CITY_API UCamera_Manager : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCamera_Manager();

	// Component

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* TopDownCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;


	// Function

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	void MoveRight(float axisvalue);



	// Variable


private:

	APlayerController * PlayerController;
	float Resolution_Y;
	float Resolution_X;
	float Mouseposition_X;
	float Mouseposition_Y;
	UGameUserSettings* UserSettings;
	//ABuilt_Manager* Manager;

		
	
};
