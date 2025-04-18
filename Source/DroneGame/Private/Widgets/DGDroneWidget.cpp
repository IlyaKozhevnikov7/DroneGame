// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/DGDroneWidget.h"
#include "Actors/BattleUnits/DGDrone.h"
#include "Components/DGCannonComponent.h"
#include "Components/DGHealthComponent.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

bool UDGDroneWidget::Initialize()
{
	bool result = Super::Initialize();

	if (APawn* Pawn = GetOwningPlayerPawn())
	{
		SetupAmmoText(Pawn);
		SetupHealthBar(Pawn);
	}

	return result;
}

void UDGDroneWidget::SetupAmmoText(APawn* Pawn)
{
	UDGCannonComponent* Cannon = Pawn->GetComponentByClass<UDGCannonComponent>();
	if (Cannon)
	{
		OnAmmoAmountChanged(Cannon);
		Cannon->OnAmmoAmountChanged.AddDynamic(this, &UDGDroneWidget::OnAmmoAmountChanged);
	}
}

void UDGDroneWidget::SetupHealthBar(APawn* Pawn)
{
	UDGHealthComponent* HealthComponent = Pawn->GetComponentByClass<UDGHealthComponent>();
	if (HealthComponent)
	{
		OnHealthChanged(HealthComponent, 0);
		HealthComponent->OnHealthChanged.AddDynamic(this, &UDGDroneWidget::OnHealthChanged);
	}
}

void UDGDroneWidget::OnAmmoAmountChanged(UDGCannonComponent* Compoment)
{
	const FText Text = FText::AsNumber(Compoment->GetAmmoAmount());
	TextBlockAmmoAmount->SetText(Text);
}

void UDGDroneWidget::OnHealthChanged(UDGHealthComponent* Compoment, int32 DeltaAmount)
{
	const int32 CurrentHealth = Compoment->GetCurrentHealth();
	const float Percent = static_cast<float>(CurrentHealth) / static_cast<float>(Compoment->GetMaxHealth());

	ProgressBarHealth->SetPercent(Percent);

	if (DeltaAmount < 0 && OnTakeDamageAnim != nullptr)
		PlayAnimation(OnTakeDamageAnim);
}
