// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DGPlayerController.generated.h"

class ADGDrone;
class UUserWidget;
enum class EDGMatchResult : uint8;

UCLASS()
class DRONEGAME_API ADGPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> EndGameWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> DroneWidgetClass;

	TObjectPtr<UUserWidget> CurrentWidget;

private:

	void BeginPlay() override;

	void OnPossess(APawn* InPawn) override;

	void SetupWidget(TSubclassOf<UUserWidget> WidgetClass);

	UFUNCTION()
	void OnMatchEnded(EDGMatchResult Result);
};
