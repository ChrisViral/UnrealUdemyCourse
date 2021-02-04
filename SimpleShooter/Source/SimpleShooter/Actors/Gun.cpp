// Copyright © Christophe Savard 2021

#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

#define OUT
//#define DRAW_DEBUG

AGun::AGun()
{
    PrimaryActorTick.bCanEverTick = false;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SetRootComponent(Root);

    Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(RootComponent);
}

void AGun::BeginPlay()
{
    Super::BeginPlay();
}

void AGun::PullTrigger()
{
    if (!Mesh)
    {
        return;
    }

    APawn* GunOwner = Cast<APawn>(GetOwner());
    if (!GunOwner)
    {
        return;
    }

    AController* Controller = GunOwner->GetController();
    if (!Controller)
    {
        return;
    }
    
    if (MuzzleFlash)
    {
        UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, MuzzleSocketName);
    }
    
    FVector ViewPosition;
    FRotator ViewRotation;
    Controller->GetPlayerViewPoint(OUT ViewPosition, OUT ViewRotation);
    const FVector Direction = ViewRotation.Vector();
    const FVector EndPosition = ViewPosition + (Direction * MaxRange);
    
    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);
    Params.AddIgnoredActor(GunOwner);
    const UWorld* World = GetWorld();
    if (World->LineTraceSingleByChannel(OUT Hit, ViewPosition, EndPosition, ECC_GameTraceChannel1, Params))
    {
        AActor* HitActor = Hit.GetActor();
        if (HitActor)
        {
            FPointDamageEvent DamageEvent(Damage, Hit, Direction, nullptr);
            HitActor->TakeDamage(Damage, DamageEvent, Controller, this);
        }

        if (ImpactEffect)
        {
            UGameplayStatics::SpawnEmitterAtLocation(World, ImpactEffect, Hit.Location, ViewRotation.GetInverse());
        }

        #ifdef DRAW_DEBUG
        const float Lifetime = 3.0f;
        DrawDebugCamera(World, ViewPosition, ViewRotation, 90.0f, 2.0f, FColor::Green, false, Lifetime);
        DrawDebugPoint(World, Hit.ImpactPoint, 5.0f, FColor::Red, false, Lifetime);
        #endif
    }
}
