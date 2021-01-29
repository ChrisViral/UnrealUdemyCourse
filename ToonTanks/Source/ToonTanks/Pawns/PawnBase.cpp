// Copyright © Christophe Savard 2021

#include "PawnBase.h"
#include "Components/CapsuleComponent.h"

APawnBase::APawnBase()
{
    PrimaryActorTick.bCanEverTick = true;

    Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
    RootComponent = Capsule;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
    BaseMesh->SetupAttachment(RootComponent);

    TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
    TurretMesh->SetupAttachment(BaseMesh);

    ProjectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn"));
    ProjectileSpawn->SetupAttachment(TurretMesh);
}
