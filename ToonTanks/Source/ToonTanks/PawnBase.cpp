// Copyright © Christophe Savard 2021

#include "PawnBase.h"

APawnBase::APawnBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APawnBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void APawnBase::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

