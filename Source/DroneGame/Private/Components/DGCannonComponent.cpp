// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/DGCannonComponent.h"
#include "Components/SphereComponent.h"

UDGCannonComponent::UDGCannonComponent()
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;
}

void UDGCannonComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeMuzzleSockets();

	if (ProjectileClass == nullptr)
		UE_LOG(LogTemp, Warning, TEXT(__FUNCDNAME__" ProjectileClass wasn`t initialized."));
}

void UDGCannonComponent::AddAmmo(uint32 Amount)
{
	SetAmmo(AmmoAmount + Amount);
}

void UDGCannonComponent::Fire(const FRotator& Direction)
{
	if (AmmoAmount == 0)
		return;

	if (MuzzleSockets.IsEmpty())
		return;

	if (ProjectileClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT(__FUNCDNAME__" ProjectileClass wasn`t initialized."));
		return;
	}

	const TObjectPtr<USceneComponent> CurrentSocket = MuzzleSockets[++NextMazzleFire % MuzzleSockets.Num()];
	
	if (GetWorld()->SpawnActor<AActor>(ProjectileClass, CurrentSocket->GetComponentLocation(), Direction))
		SetAmmo(AmmoAmount - 1);
}

void UDGCannonComponent::SetAmmo(uint32 Amount)
{
	if (AmmoAmount != Amount)
	{
		AmmoAmount = Amount;
		OnAmmoAmountChanged.Broadcast(this);
	}
}

void UDGCannonComponent::InitializeMuzzleSockets()
{
	TArray<UActorComponent*> Components = GetOwner()->GetComponentsByTag(USceneComponent::StaticClass(), "MuzzleSocket");
	if (Components.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT(__FUNCDNAME__" failed to find any component with \"MuzzleSocket\" tag."));
		return;
	}

	for (auto Mazzle : Components)
		MuzzleSockets.Add(Cast<USceneComponent>(Mazzle));
}
