// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DGHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, UDGHealthComponent*, Component, int32, DeltaAmount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDiedSignature, AActor*, Actor);

UCLASS(BlueprintType)
class DRONEGAME_API UDGHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnDiedSignature OnDied;

private:

	UPROPERTY(EditDefaultsOnly, meta=(min="0"))
	int32 MaxHealth = 100.f;

	int32 CurrentHealth = MaxHealth;

public:

	UDGHealthComponent();

	bool HasFullHealth() const
	{
		return CurrentHealth == MaxHealth;
	}

	int32 GetMaxHealth() const
	{
		return MaxHealth;
	}

	int32 GetCurrentHealth() const
	{
		return CurrentHealth;
	}

	void AddHealth(int32 Amount);

private:

	void SetHealth(int32 Amount);
};
