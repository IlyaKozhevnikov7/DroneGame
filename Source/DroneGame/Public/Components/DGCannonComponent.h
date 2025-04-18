// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DGCannonComponent.generated.h"

class ADGBattleUnit;
class USceneComponent;
class UDGCannonComponent;
enum class EDGMatchResult : uint8;

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
	
	UPROPERTY(EditDefaultsOnly)
	float FiringRate = 0.2f;

	UPROPERTY(EditDefaultsOnly)
	uint32 AmmoAmount;
	
	uint32 NextMazzleFire = 0;

	TArray<TObjectPtr<USceneComponent>> MuzzleSockets;

	TObjectPtr<ADGBattleUnit> Unit;

	FTimerHandle FireTimer;

public:

	UDGCannonComponent();

private:

	void BeginPlay() override;

public:

	bool CanFire() const
	{
		return AmmoAmount > 0;
	}

	uint32 GetAmmoAmount() const
	{
		return AmmoAmount;
	}

	void AddAmmo(uint32 Amount);

	void StartFire();

	void StopFire();

private:

	void SetAmmo(uint32 Amount);

	void InitializeMuzzleSockets();

	void MakeShot();

	UFUNCTION()
	void OnMatchEnded(EDGMatchResult Result);
};
