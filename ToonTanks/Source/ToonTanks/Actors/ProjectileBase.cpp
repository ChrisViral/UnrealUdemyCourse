// Copyright © Christophe Savard 2021

#include "ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AProjectileBase::AProjectileBase()
{
    PrimaryActorTick.bCanEverTick = false;
    ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
    RootComponent = ProjectileMesh;

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
    ProjectileMovement->InitialSpeed = Speed;
    ProjectileMovement->MaxSpeed = Speed;
    InitialLifeSpan = Lifespan;
}

void AProjectileBase::BeginPlay()
{
    Super::BeginPlay();

    ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* Other, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    AActor* OwnerActor = GetOwner();
    if (!OwnerActor || !Other || Other == this || Other == OwnerActor)
    {
        Destroy();
        return;
    }

    UGameplayStatics::ApplyDamage(Other, Damage, OwnerActor->GetInstigatorController() ,this, DamageType);
    Destroy();
}
