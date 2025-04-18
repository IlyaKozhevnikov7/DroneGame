// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/DGEndGameWidget.h"
#include "Actors/DGGameMode.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

bool UDGEndGameWidget::Initialize()
{
	bool Result = Super::Initialize();

	if (ButtonPlayAgain)
		ButtonPlayAgain->OnClicked.AddDynamic(this, &UDGEndGameWidget::OnClickedPlayAgain);

	if (ButtonBackToMenu)
		ButtonBackToMenu->OnClicked.AddDynamic(this, &UDGEndGameWidget::OnClickedBackToMenu);

	return Result;
}

void UDGEndGameWidget::SetMatchResult(EDGMatchResult Result)
{
	TextBlockTitle->SetText(FText::FromString(Result == EDGMatchResult::Victory ? "Victory" : "Defeat"));
}


void UDGEndGameWidget::OnClickedPlayAgain()
{
	GetWorld()->GetAuthGameMode<ADGGameMode>()->RestartGame();
}

void UDGEndGameWidget::OnClickedBackToMenu()
{
	UGameplayStatics::OpenLevel(this, FName("L_Menu"));
}