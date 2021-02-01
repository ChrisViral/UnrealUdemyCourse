// Copyright © Christophe Savard 2021

#include "ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AProjectileBase::AProjectileBase()
{
    PrimaryActorTick.bCanEverTick = false;

    ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
    RootComponent = ProjectileMesh;

    TrailEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Effect"));
    TrailEffect->SetupAttachment(RootComponent);

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
    ProjectileMovement->InitialSpeed = Speed;
    ProjectileMovement->MaxSpeed = Speed;
    InitialLifeSpan = Lifespan;
}

void AProjectileBase::BeginPlay()
{
    Super::BeginPlay();

    ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
    UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* Other, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    AActor* OwnerActor = GetOwner();
    if (OwnerActor && Other && Other != this && Other != OwnerActor)
    {
        UGameplayStatics::ApplyDamage(Other, Damage, OwnerActor->GetInstigatorController() ,this, DamageType);
        if (UGameplayStatics::GetPlayerPawn(this, 0) == Other)
        {
            GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(HitShake);
        }
    }

    const FVector Position = GetActorLocation();
    UGameplayStatics::SpawnEmitterAtLocation(this, HitEffect, Position);
    UGameplayStatics::PlaySoundAtLocation(this, HitSound, Position);
    Destroy();
}
