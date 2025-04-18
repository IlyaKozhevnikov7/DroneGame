// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/BattleUnits/DGDrone.h"
#include "Actors/DGGameMode.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Components/DGCannonComponent.h"

ADGDrone::ADGDrone()
{
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	checkf(Camera != nullptr, TEXT("ADGDrone::ADGDrone failed to create UCameraComponent."));
	Camera->SetupAttachment(GetRootComponent());

	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void ADGDrone::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetAuthGameMode<ADGGameMode>()->OnMatchEnded.AddDynamic(this, &ADGDrone::OnMatchEnded);
}

void ADGDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateLocation(DeltaTime);
}

void ADGDrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADGDrone::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADGDrone::MoveRight);
	PlayerInputComponent->BindAxis("MoveUp", this, &ADGDrone::MoveUp);
	
	PlayerInputComponent->BindAxis("LookUp", this, &ADGDrone::LookUp);
	PlayerInputComponent->BindAxis("Rotate", this, &ADGDrone::Rotate);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, GetCannonComponent().Get(), &UDGCannonComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, GetCannonComponent().Get(), &UDGCannonComponent::StopFire);
}

void ADGDrone::UpdateLocation(float DeltaTime)
{
	const FVector NewLocation = GetActorLocation() + MoveDirection * MoveSpeed * DeltaTime;
	SetActorLocation(NewLocation, true);
	MoveDirection = FVector::ZeroVector;
}

void ADGDrone::MoveForward(float Direction)
{
	AddDirection(GetActorForwardVector() * Direction);
}

void ADGDrone::MoveRight(float Direction)
{
	AddDirection(GetActorRightVector() * Direction);
}

void ADGDrone::MoveUp(float Direction)
{
	AddDirection(GetActorUpVector() * Direction);
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

void ADGDrone::OnMatchEnded(EDGMatchResult Result)
{
	SetActorTickEnabled(false);
}
