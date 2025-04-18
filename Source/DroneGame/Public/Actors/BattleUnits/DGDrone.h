// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BattleUnits/DGBattleUnit.h"
#include "DGDrone.generated.h"

class USphereComponent;
class UCameraComponent;
class UDGCannonComponent;
class UUserWidget;
enum class EDGMatchResult : uint8;

UCLASS()
class DRONEGAME_API ADGDrone : public ADGBattleUnit
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
	TObjectPtr<UCameraComponent> Camera;

	FVector MoveDirection;

	float LookUpDirection;
	
	float RotationDirection;

public:

	ADGDrone();

private:

	void BeginPlay() override;

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void Tick(float DeltaTime) override;

public:

	void AddDirection(FVector Direction)
	{
		(MoveDirection += Direction).Normalize();
	}

	void LookUp(float Value);

	void Rotate(float Value);

private:

	void UpdateLocation(float DeltaTime);

	void MoveForward(float Direction);

	void MoveRight(float Direction);

	void MoveUp(float Direction);



	UFUNCTION()
	void OnMatchEnded(EDGMatchResult Result);
};
