// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Pickups/DGAmmoPickup.h"
#include "Components/DGCannonComponent.h"

void ADGAmmoPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (UDGCannonComponent* Cannon = OtherActor->GetComponentByClass<UDGCannonComponent>())
	{
		Cannon->AddAmmo(Amount);
		Destroy();
	}
}
