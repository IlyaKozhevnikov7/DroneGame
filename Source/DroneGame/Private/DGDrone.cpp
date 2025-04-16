// Fill out your copyright notice in the Description page of Project Settings.

#include "DGDrone.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Components/DGHealthComponent.h"

ADGDrone::ADGDrone()
{	
	Collision = CreateDefaultSubobject<USphereComponent>("Collision Component");
	checkf(Collision != nullptr, TEXT("ADGDron::ADGDron failed to create USphereComponent."));
	SetRootComponent(Collision);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	checkf(Camera != nullptr, TEXT("ADGDron::ADGDron failed to create UCameraComponent."));
	Camera->SetupAttachment(Collision);

	UDGHealthComponent* HealthComponent = CreateDefaultSubobject<UDGHealthComponent>("Health Component");
	checkf(HealthComponent != nullptr, TEXT("ADGDron::ADGDron failed to create UDGHealthComponent."));

	PrimaryActorTick.bCanEverTick = true;
}

void ADGDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateLocation(DeltaTime);
}

void ADGDrone::LookUp(float Value)
{
	if (Camera == nullptr)
		return;

	const FRotator Rotation = Camera->GetRelativeRotation();

	const float NewPitch = FMath::Clamp(
		Rotation.Pitch + Value * LookUpSensitivity,
		-PitchConstraint,
		PitchConstraint);

	Camera->SetRelativeRotation(FRotator(NewPitch, Rotation.Yaw, Rotation.Roll));
}

void ADGDrone::Rotate(float Value)
{
	const FRotator Rotation = RootComponent->GetRelativeRotation();
	RootComponent->SetRelativeRotation(FRotator(Rotation.Pitch, Rotation.Yaw + Value * RotationSensitivity, Rotation.Roll));
}

void ADGDrone::UpdateLocation(float DeltaTime)
{
	const FVector NewLocation = GetActorLocation() + MoveDirection * MoveSpeed * DeltaTime;
	SetActorLocation(NewLocation);
	MoveDirection = FVector::ZeroVector;
}
