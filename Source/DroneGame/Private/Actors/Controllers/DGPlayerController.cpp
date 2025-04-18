// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Controllers/DGPlayerController.h"
#include "Actors/BattleUnits/DGDrone.h"
#include "Widgets/DGEndGameWidget.h"
#include "Actors/DGGameMode.h"

void ADGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetAuthGameMode<ADGGameMode>()->OnMatchEnded.AddDynamic(this, &ADGPlayerController::OnMatchEnded);
}

void ADGPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (InPawn == nullptr)
		return;

	if (InPawn->IsA<ADGDrone>())
	{
		SetupWidget(DroneWidgetClass);
		SetInputMode(FInputModeGameOnly());
		SetShowMouseCursor(false);
		EnableInput(this);
	}
}

void ADGPlayerController::SetupWidget(TSubclassOf<UUserWidget> WidgetClass)
{
	if (CurrentWidget != nullptr)
		CurrentWidget->RemoveFromParent();

	if (WidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget(this, WidgetClass);
		CurrentWidget->AddToViewport();
	}
}

void ADGPlayerController::OnMatchEnded(EDGMatchResult Result)
{
	SetupWidget(EndGameWidgetClass);
	
	SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);

	if (UDGEndGameWidget* Widget = Cast<UDGEndGameWidget>(CurrentWidget))
		Widget->SetMatchResult(Result);
}
