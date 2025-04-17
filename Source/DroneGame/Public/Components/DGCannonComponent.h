// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DGCannonComponent.generated.h"

class USceneComponent;
class UDGCannonComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAmmoAmountChangedSignature, UDGCannonComponent*, Component);

UCLASS(BlueprintType)
class DRONEGAME_API UDGCannonComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnAmmoAmountChangedSignature OnAmmoAmountChanged;

private:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ProjectileClass;
	
	uint32 AmmoAmount;
	
	uint32 NextMazzleFire = 0;

	TArray<TObjectPtr<USceneComponent>> MuzzleSockets;

public:

	UDGCannonComponent();

private:

	void BeginPlay() override;

public:

	uint32 GetAmmoAmount() const
	{
		return AmmoAmount;
	}

	void AddAmmo(uint32 Amount);

	void Fire(const FRotator& Direction);

private:

	void SetAmmo(uint32 Amount);

	void InitializeMuzzleSockets();
};
