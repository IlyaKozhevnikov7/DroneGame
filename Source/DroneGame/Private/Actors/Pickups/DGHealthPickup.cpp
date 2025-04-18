// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Pickups/DGHealthPickup.h"
#include "Components/DGHealthComponent.h"

void ADGHealthPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (UDGHealthComponent* Health = OtherActor->GetComponentByClass<UDGHealthComponent>())
	{
		if (Health->HasFullHealth())
			return;

		Health->AddHealth(Amount);
		Destroy();
	}
}
