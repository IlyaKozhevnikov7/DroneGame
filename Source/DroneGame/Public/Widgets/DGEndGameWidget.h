// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DGEndGameWidget.generated.h"

class UTextBlock;
class UButton;
enum class EDGMatchResult : uint8;

UCLASS()
class DRONEGAME_API UDGEndGameWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlockTitle;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonPlayAgain;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonBackToMenu;

private:

	bool Initialize() override;

public:

	void SetMatchResult(EDGMatchResult Result);

private:

	UFUNCTION()
	void OnClickedPlayAgain();

	UFUNCTION()
	void OnClickedBackToMenu();
};
