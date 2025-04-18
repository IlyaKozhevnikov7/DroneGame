// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/DGGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"
#include "Actors/BattleUnits/DGDrone.h"
#include "Actors/BattleUnits/DGTurret.h"
#include "Actors/Controllers/DGTurretController.h"
#include "Components/DGHealthComponent.h"
#include "Algo/Count.h"

void ADGGameMode::OnPostLogin(AController* NewPlayer)
{
	Initialize();
	RestartGame();
}

void ADGGameMode::Initialize()
{
	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		APlayerStart* Current = *It;
	
		if (PlayerStart == nullptr && Current->PlayerStartTag == PlayerStartTag)
		{
			PlayerStart = Current;
			continue;
		}

		if (TSubclassOf<AActor>* ActorClass = StartSpotClasses.Find(Current->PlayerStartTag))
		{
			TArray<FSpotInfo>& SpotArray = ActorSpots.FindOrAdd(*ActorClass);
			SpotArray.Add(FSpotInfo(Current));
		}
	}

	if (PlayerStart == nullptr)
		UE_LOG(LogTemp, Warning, TEXT(__FUNCDNAME__" There is not player start on level."));
}

void ADGGameMode::RestartGame()
{
	ClearLevel();
	SpawnPlayer();
	SpawnActors();
}

void ADGGameMode::SpawnPlayer()
{
	if (PlayerStart == nullptr)
		return;

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	ADGDrone* Drone = GetWorld()->SpawnActor<ADGDrone>(DefaultPawnClass);

	Drone->SetActorLocationAndRotation(PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation());
	PlayerController->SetPawn(Drone);
	PlayerController->Possess(Drone);

	Drone->GetHealthComponent()->OnDied.AddDynamic(this, &ADGGameMode::OnDied);
}

void ADGGameMode::SpawnActors()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (auto& Spots : ActorSpots)
	{
		for (FSpotInfo& Info : Spots.Value)
		{
			if (TObjectPtr<AActor> Actor = GetWorld()->SpawnActor<AActor>(Spots.Key, Info.Spot->GetActorLocation(), Info.Spot->GetActorRotation(), SpawnParams))
			{
				if (TObjectPtr<UDGHealthComponent> Health = Actor->GetComponentByClass<UDGHealthComponent>())
					Health->OnDied.AddDynamic(this, &ADGGameMode::OnDied);

				Info.CurrentActor = Actor;
			}
		}
	}
}

void ADGGameMode::ClearLevel()
{
	for (auto& Spots : ActorSpots)
		for (const FSpotInfo& Info : Spots.Value)
			if (Info.CurrentActor != nullptr)
				Info.CurrentActor->Destroy();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (APawn* Pawn = PlayerController->GetPawn())
		Pawn->Destroy();
}

void ADGGameMode::OnDied(AActor* Actor)
{
	if (Actor->IsA<ADGTurret>())
	{
		if (auto Turrets = ActorSpots.Find(Actor->GetClass()))
		{
			if (FSpotInfo* Info = (*Turrets).FindByPredicate([=](FSpotInfo& Info) { return Info.CurrentActor == Actor; }))
			{
				Info->CurrentActor = nullptr;
				Actor->Destroy();
			}

			if (Algo::CountIf(*Turrets, [](const FSpotInfo& Info) { return Info.CurrentActor != nullptr; }) == 0)
				OnMatchEnded.Broadcast(EDGMatchResult::Victory);
		}
	}
	else if (Actor->IsA<ADGDrone>())
	{
		OnMatchEnded.Broadcast(EDGMatchResult::Defeat);
	}
}
