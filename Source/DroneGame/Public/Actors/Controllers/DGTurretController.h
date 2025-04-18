// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DGTurretController.generated.h"

class ADGTurret;

UCLASS()
class DRONEGAME_API ADGTurretController : public AAIController
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditDefaultsOnly, meta=(min="0"))
	float DetectionRadius = 5000.f;

	UPROPERTY(EditDefaultsOnly, meta= (min = "0"))
	float RotationSpeed = 5.f;

	TObjectPtr<ADGTurret> Turret;

	bool bIsFiring = false;

public:

	ADGTurretController();

private:

	void OnPossess(APawn* InPawn) override;

	void Tick(float DeltaTime) override;

	void UpdateBehavior(float DeltaTime);

	void RotateTo(const FVector& Target, float DeltaTime);
};
