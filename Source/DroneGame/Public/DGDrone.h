// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DGDrone.generated.h"

class USphereComponent;
class UCameraComponent;

UCLASS()
class DRONEGAME_API ADGDrone : public APawn
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly)
	float MoveSpeed = 300.f;

	UPROPERTY(EditDefaultsOnly)
	float LookUpSensitivity = 5.f;

	UPROPERTY(EditDefaultsOnly)
	float RotationSensitivity = 5.f;

	UPROPERTY(EditDefaultsOnly)
	float PitchConstraint = 45.f;

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* Collision = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* Camera = nullptr;

	FVector MoveDirection;

	float LookUpDirection;
	
	float RotationDirection;

public:

	ADGDrone();

private:

	virtual void Tick(float DeltaTime) override;

public:

	void AddDirection(FVector Direction)
	{
		(MoveDirection += Direction).Normalize();
	}

	void LookUp(float Value);

	void Rotate(float Value);

private:

	void UpdateLocation(float DeltaTime);
};
