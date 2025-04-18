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

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ADGPickupBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	constexpr float RotationSpeed = 50.f;
	constexpr float Amplitude = 15.f;
	constexpr float Frequency = 1.5f;

	Mesh->AddWorldRotation(FRotator(0.f, RotationSpeed * DeltaSeconds, 0.f));

	FVector NewLocation = Mesh->GetRelativeLocation();
	NewLocation.Z = Amplitude * FMath::Sin(Frequency * GetWorld()->GetTimeSeconds());
	Mesh->SetRelativeLocation(NewLocation);
}