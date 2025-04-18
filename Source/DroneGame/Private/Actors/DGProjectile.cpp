// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/DGProjectile.h"
#include "Components/SphereComponent.h"
#include "Components/DGHealthComponent.h"

ADGProjectile::ADGProjectile()
{
	Collision = CreateDefaultSubobject<USphereComponent>("Collison");
	Collision->InitSphereRadius(5.f);
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(Collision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Collision);

	PrimaryActorTick.bCanEverTick = true;
}

void ADGProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeTime);
}

void ADGProjectile::TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);

	const FVector DeltaLocation = GetActorForwardVector() * Speed * DeltaTime;
	SetActorLocation(GetActorLocation() + DeltaLocation, true);
}

void ADGProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (UDGHealthComponent* Health = OtherActor->GetComponentByClass<UDGHealthComponent>())
		Health->AddHealth(-DamageAmount);

	Destroy();
}

void ADGProjectile::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	Destroy();
}