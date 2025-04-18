// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/BattleUnits/DGTurret.h"
#include "Actors/Controllers/DGTurretController.h"

ADGTurret::ADGTurret()
{
	AIControllerClass = ADGTurretController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	PrimaryActorTick.bCanEverTick = true;
}
