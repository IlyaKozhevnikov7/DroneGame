// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/BattleUnits/DGBattleUnit.h"
#include "Components/SphereComponent.h"
#include "Components/DGHealthComponent.h"
#include "Components/DGCannonComponent.h"

ADGBattleUnit::ADGBattleUnit()
{
	Collision = CreateDefaultSubobject<USphereComponent>("Collision Component");
	checkf(Collision != nullptr, TEXT(__FUNCDNAME__" failed to create USphereComponent."));
	SetRootComponent(Collision);

	HealthComponent = CreateDefaultSubobject<UDGHealthComponent>("Health Component");
	checkf(HealthComponent != nullptr, TEXT(__FUNCDNAME__" failed to create UDGHealthComponent."));

	CannonComponent = CreateDefaultSubobject<UDGCannonComponent>("Cannon Component");
	checkf(CannonComponent != nullptr, TEXT(__FUNCDNAME__" failed to create UDGCannonComponent."));

	PrimaryActorTick.bCanEverTick = true;
}

void ADGBattleUnit::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnDied.AddDynamic(this, &ADGBattleUnit::OnDied);
}

FRotator ADGBattleUnit::GetAimRotation()
{
	return IsPlayerControlled()
		? GetBaseAimRotation()
		: GetActorRotation();
}

void ADGBattleUnit::OnDied(AActor* Actor)
{
	Destroy();
}
