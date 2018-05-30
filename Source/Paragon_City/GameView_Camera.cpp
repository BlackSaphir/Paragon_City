// Fill out your copyright notice in the Description page of Project Settings.

#include "GameView_Camera.h"

void AGameView_Camera::BeginPlay()
{
	Super::BeginPlay();

	GetCameraComponent()->SetConstraintAspectRatio(false);
}
