// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/DGHealthComponent.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"

UDGHealthComponent::UDGHealthComponent()
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;
}

void UDGHealthComponent::AddHealth(int32 Amount)
{
	SetHealth(CurrentHealth + Amount);
}

void UDGHealthComponent::SetHealth(int32 Amount)
{
	if (CurrentHealth == Amount)
		return;

	const int32 Delta = Amount - CurrentHealth;
	CurrentHealth = FMath::Clamp(Amount, 0, MaxHealth);
	OnHealthChanged.Broadcast(this, Delta);

	if (CurrentHealth == 0)
		OnDied.Broadcast(GetOwner());
}