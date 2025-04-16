// Fill out your copyright notice in the Description page of Project Settings.

#include "DGPlayerController.h"
#include "DGDrone.h"

void ADGPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (InPawn == nullptr)
	{
		Drone = nullptr;
		return;
	}

	if (ADGDrone* DronePawn = Cast<ADGDrone>(InPawn))
	{
		Drone = DronePawn;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ADGPlayerController must receive ADGDrone pawn."));
	}
}

void ADGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ADGPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ADGPlayerController::MoveRight);
	InputComponent->BindAxis("MoveUp", this, &ADGPlayerController::MoveUp);

	InputComponent->BindAxis("LookUp", this, &ADGPlayerController::LookUp);
	InputComponent->BindAxis("Rotate", this, &ADGPlayerController::Rotate);
}

void ADGPlayerController::MoveForward(float Value)
{
	if (Drone != nullptr)
		Drone->AddDirection(Drone->GetActorForwardVector() * Value);
}

void ADGPlayerController::MoveRight(float Value)
{
	if (Drone != nullptr)
        Drone->AddDirection(Drone->GetActorRightVector() * Value);
}

void ADGPlayerController::MoveUp(float Value)
{
	if (Drone != nullptr)
		Drone->AddDirection(Drone->GetActorUpVector() * Value);
}

void ADGPlayerController::LookUp(float Value)
{
	if (Drone != nullptr)
		Drone->LookUp(Value);
}

void ADGPlayerController::Rotate(float Value)
{
	if (Drone != nullptr)
		Drone->Rotate(Value);
}