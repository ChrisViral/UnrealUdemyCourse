// Copyright © Christophe Savard 2021

#include "PawnTurret.h"

APawnTurret::APawnTurret()
{

}

void APawnTurret::BeginPlay()
{
    Super::BeginPlay();
}

void APawnTurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APawnTurret::Tick(const float DeltaTime)
{
    Super::Tick(DeltaTime);
}
