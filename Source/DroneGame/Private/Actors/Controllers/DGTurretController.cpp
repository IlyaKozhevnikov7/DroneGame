// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Controllers/DGTurretController.h"
#include "Actors/BattleUnits/DGTurret.h"
#include "Components/DGCannonComponent.h"

ADGTurretController::ADGTurretController()
{
    PrimaryActorTick.bStartWithTickEnabled = false;
    PrimaryActorTick.bCanEverTick = true;
}

void ADGTurretController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    Turret = Cast<ADGTurret>(InPawn);
    SetActorTickEnabled(Turret != nullptr);
}

void ADGTurretController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    UpdateBehavior(DeltaTime);
}

void ADGTurretController::UpdateBehavior(float DeltaTime)
{
    if (Turret == nullptr)
        return;

    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController == nullptr)
        return;

    APawn* PlayerPawn = PlayerController->GetPawn();
    if (PlayerPawn == nullptr)
        return;

    const FVector PlayerLocation = PlayerPawn->GetActorLocation();
    const float Distance = FVector::Dist(Turret->GetActorLocation(), PlayerLocation);

    if (Distance <= DetectionRadius)
    {
        if (bIsFiring == false)
        {
            Turret->GetCannonComponent()->StartFire();
            bIsFiring = true;
        }

        FVector ToPlayer = PlayerLocation;
        RotateTo(ToPlayer, DeltaTime);
    }
    else
    {
        if (bIsFiring)
        {
            Turret->GetCannonComponent()->StopFire();
            bIsFiring = false;
        }
    }
}

void ADGTurretController::RotateTo(const FVector& Target, float DeltaTime)
{
    const FVector Direction = (Target - Turret->GetActorLocation()).GetSafeNormal();
    const FRotator TargeRotation = Direction.Rotation();
    const FRotator CurrentRotation = Turret->GetActorRotation();
    FRotator NewRotation = FMath::RInterpTo(Turret->GetActorRotation(), TargeRotation, DeltaTime, RotationSpeed);

    NewRotation.Roll = CurrentRotation.Roll;
    Turret->SetActorRotation(NewRotation);
}