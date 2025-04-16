// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DGPlayerController.generated.h"

class ADGDrone;

UCLASS()
class DRONEGAME_API ADGPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:

	ADGDrone* Drone = nullptr;

private:

	void OnPossess(APawn* InPawn) override;

	void SetupInputComponent() override;

	void MoveForward(float value);

	void MoveRight(float value);

	void MoveUp(float value);

	void LookUp(float value);

	void Rotate(float value);
};
