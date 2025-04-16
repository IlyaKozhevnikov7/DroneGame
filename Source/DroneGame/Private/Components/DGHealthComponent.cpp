// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/DGHealthComponent.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"

UDGHealthComponent::UDGHealthComponent()
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;
}

void UDGHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner() == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UDGHealthComponent::BeginPlay GetOwner return nullprt."));
		return;
	}

	USphereComponent* Collision = GetOwner()->GetComponentByClass<USphereComponent>();
	if (Collision == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UDGHealthComponent::BeginPlay failed to get USphereComponent from %s."), *GetOwner()->GetName());
		return;
	}

	Collision->OnComponentBeginOverlap.AddDynamic(this, &UDGHealthComponent::OnCollisionBeginOverlap);
}

void UDGHealthComponent::OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("UDGHealthComponent::OnCollisionBeginOverlap %s."), *(OtherActor->GetName()));
}


