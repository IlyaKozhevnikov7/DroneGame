// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DGGameMode.generated.h"

class ADGTurret;

UENUM()
enum class EDGMatchResult : uint8
{
	Victory = 0,
	Defeat
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMatchEndedSignature, EDGMatchResult, Result);

struct FSpotInfo
{
	TObjectPtr<APlayerStart> Spot;
	TObjectPtr<AActor> CurrentActor;

	FSpotInfo(TObjectPtr<APlayerStart> Spot) :
		Spot(Spot),
		CurrentActor(nullptr)
	{
	}
};

UCLASS()
class DRONEGAME_API ADGGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintAssignable)
	FOnMatchEndedSignature OnMatchEnded;

private:

	UPROPERTY(EditDefaultsOnly)
	FName PlayerStartTag = "Player";

	UPROPERTY(EditDefaultsOnly)
	TMap<FName, TSubclassOf<AActor>> StartSpotClasses;

	TMap<TSubclassOf<AActor>, TArray<FSpotInfo>> ActorSpots;

	TObjectPtr<APlayerStart> PlayerStart;

private:

	void OnPostLogin(AController* NewPlayer) override;

public:

	void RestartGame();

private:

	void Initialize();

	void SpawnPlayer();

	void SpawnActors();

	void ClearLevel();

	UFUNCTION()
	void OnDied(AActor* Actor);
};
