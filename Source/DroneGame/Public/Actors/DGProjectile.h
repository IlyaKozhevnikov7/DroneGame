// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DGProjectile.generated.h"

class USphereComponent;

UCLASS()
class DRONEGAME_API ADGProjectile : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditDefaultsOnly, meta = (min = "0"))
	float Speed = 7500.f;

	UPROPERTY(EditDefaultsOnly, meta=(min="0"))
	float LifeTime = 3.f;

	UPROPERTY(EditDefaultsOnly, meta = (min = "0"))
	int32 DamageAmount = 5;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USphereComponent> Collision;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> Mesh;

public:

	ADGProjectile();

private:

	void BeginPlay() override;

	void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;

	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
};
