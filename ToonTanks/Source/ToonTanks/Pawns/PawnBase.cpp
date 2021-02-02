// Copyright � Christophe Savard 2021

#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Actors/ProjectileBase.h"
#include "ToonTanks/Components/HealthComponent.h"

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

    Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

void APawnBase::LookAt(const FVector Target)
{
    const FVector TurretLocation = TurretMesh->GetComponentLocation();
    const FVector TargetLocation = FVector(Target.X, Target.Y, TurretLocation.Z);
    TurretMesh->SetWorldRotation((TargetLocation - TurretLocation).Rotation());
}

void APawnBase::Fire()
{
    if (ProjectileClass)
    {
        AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass,
                                                                              ProjectileSpawn->GetComponentLocation(),
                                                                              ProjectileSpawn->GetComponentRotation());
        Projectile->SetOwner(this);
    }
}

void APawnBase::OnDestroy()
{
    const FVector Position = GetActorLocation();
    UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionEffect, Position);
    UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, Position);
}