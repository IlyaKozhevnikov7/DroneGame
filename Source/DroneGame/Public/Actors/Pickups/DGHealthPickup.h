// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pickups/DGPickupBase.h"
#include "DGHealthPickup.generated.h"

UCLASS()
class DRONEGAME_API ADGHealthPickup : public ADGPickupBase
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditDefaultsOnly)
	uint32 Amount = 20;

private:
	
	void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
