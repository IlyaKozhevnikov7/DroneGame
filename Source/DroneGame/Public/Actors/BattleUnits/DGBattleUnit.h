// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DGBattleUnit.generated.h"

class USphereComponent;
class UDGHealthComponent;
class UDGCannonComponent;

UCLASS()
class DRONEGAME_API ADGBattleUnit : public APawn
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USphereComponent> Collision;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDGHealthComponent> HealthComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDGCannonComponent> CannonComponent;

public:

	ADGBattleUnit();

protected:

	void BeginPlay() override;

public:

	TObjectPtr<UDGHealthComponent> GetHealthComponent() const
	{
		return HealthComponent;
	}
	
	TObjectPtr<UDGCannonComponent> GetCannonComponent() const
	{
		return CannonComponent;
	}

	FRotator GetAimRotation();

private:

	UFUNCTION()
	void OnDied(AActor* Actor);
};
