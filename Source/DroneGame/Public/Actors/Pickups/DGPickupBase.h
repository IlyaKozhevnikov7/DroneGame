// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DGPickupBase.generated.h"

class USphereComponent;

UCLASS()
class DRONEGAME_API ADGPickupBase : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USphereComponent> Collision;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> Mesh;
	
public:

	ADGPickupBase();
};
