// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Pickups/DGPickupBase.h"
#include "Components/SphereComponent.h"

ADGPickupBase::ADGPickupBase()
{
	Collision = CreateDefaultSubobject<USphereComponent>("Collison");
	Collision->InitSphereRadius(80.f);
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(Collision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Collision);
}
