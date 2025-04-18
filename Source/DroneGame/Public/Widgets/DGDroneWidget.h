// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DGDroneWidget.generated.h"

class UTextBlock;
class UProgressBar;
class UDGCannonComponent;
class UDGHealthComponent;

UCLASS()
class DRONEGAME_API UDGDroneWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlockAmmoAmount;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBarHealth;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> OnTakeDamageAnim;

private:

	bool Initialize() override;

	void SetupAmmoText(APawn* Pawn);

	void SetupHealthBar(APawn* Pawn);

	UFUNCTION()
	void OnAmmoAmountChanged(UDGCannonComponent* Compoment);

	UFUNCTION()
	void OnHealthChanged(UDGHealthComponent* Compoment, int32 DeltaAmount);
};
