// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/DGCannonComponent.h"
#include "Components/SphereComponent.h"
#include "Actors/BattleUnits/DGBattleUnit.h"
#include "Actors/DGGameMode.h"

UDGCannonComponent::UDGCannonComponent()
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;
}

void UDGCannonComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeMuzzleSockets();

	Unit = GetOwner<ADGBattleUnit>();
	GetWorld()->GetAuthGameMode<ADGGameMode>()->OnMatchEnded.AddDynamic(this, &UDGCannonComponent::OnMatchEnded);

	if (ProjectileClass == nullptr)
		UE_LOG(LogTemp, Warning, TEXT(__FUNCDNAME__" ProjectileClass wasn`t initialized."));
}

void UDGCannonComponent::AddAmmo(uint32 Amount)
{
	SetAmmo(AmmoAmount + Amount);
}

void UDGCannonComponent::StartFire()
{
	if (CanFire() == false)
		return;

	if (Unit == nullptr)
		return;
	
	if (MuzzleSockets.IsEmpty())
		return;
	
	if (ProjectileClass == nullptr)
		return;

	GetWorld()->GetTimerManager().SetTimer(
		FireTimer,
		this,
		&UDGCannonComponent::MakeShot,
		FiringRate,
		true,
		0.f);
}

void UDGCannonComponent::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(FireTimer);
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

void UDGCannonComponent::MakeShot()
{
	if (CanFire() == false)
	{
		StopFire();
		return;
	}

	const TObjectPtr<USceneComponent> CurrentSocket = MuzzleSockets[++NextMazzleFire % MuzzleSockets.Num()];
	if (GetWorld()->SpawnActor<AActor>(ProjectileClass, CurrentSocket->GetComponentLocation(), Unit->GetAimRotation()) != nullptr)
		SetAmmo(AmmoAmount - 1);
}

void UDGCannonComponent::OnMatchEnded(EDGMatchResult Result)
{
	StopFire();
}