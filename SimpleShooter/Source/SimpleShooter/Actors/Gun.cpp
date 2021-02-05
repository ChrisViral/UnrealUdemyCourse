// Copyright © Christophe Savard 2021

#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/EnumProperty.h"

#define OUT
#define DEBUG
#ifdef DEBUG
#include "DrawDebugHelpers.h"
#endif

constexpr float GRecoveryTolerance = 0.5f;

AGun::AGun()
{
    PrimaryActorTick.bCanEverTick = true;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SetRootComponent(Root);

    Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(RootComponent);
}

void AGun::BeginPlay()
{
    Super::BeginPlay();

    Transform = GetTransform();
    Drift *= MaxRange;
}

void AGun::Tick(const float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (CurrentSpread > 0.0f)
    {
        CurrentSpread -= CurrentSpread * RecoverFactor * DeltaTime;
        if (CurrentSpread <= GRecoveryTolerance)
        {
            CurrentSpread = 0.0f;
        }
        UE_LOG(LogTemp, Warning, TEXT("Current spread: %f"), CurrentSpread);
    }
}

void AGun::PullTrigger()
{
    if (!Initialize())
    {
        return;
    }

    MuzzleEffects();
    
    FVector StartPosition;
    FVector EndPosition;
    FRotator Direction;
    GetViewpoint(OUT StartPosition, OUT EndPosition, OUT Direction);
    
    FHitResult Hit;
    if (CheckHit(OUT Hit, StartPosition, EndPosition))
    {
        ApplyDamage(Hit, Direction.Vector());
        ImpactEffects(Hit, Direction.GetInverse());

        #ifdef DEBUG
        //DrawDebugCamera(World, StartPosition, Direction, 90.0f, 2.0f, FColor::Green, false, Lifetime);
        DrawDebugPoint(GetWorld(), Hit.ImpactPoint, 5.0f, FColor::Red, false, 5.0f);
        #endif
    }
}

bool AGun::Initialize()
{
    if (!bInitialized)
    {
        bInitialized = true;
        Owner = Cast<APawn>(GetOwner());
        if (Owner)
        {
            Controller = Owner->GetController();
            if (!Controller)
            {
                UE_LOG(LogTemp, Warning, TEXT("Gun %s's owner has no controller"), *GetName());
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Gun %s has no owner"), *GetName());
        }
    }

    return Mesh && Owner && Controller;
}

void AGun::GetViewpoint(FVector& OutStartPosition, FVector& OutEndPosition, FRotator& OutDirection)
{
    Controller->GetPlayerViewPoint(OUT OutStartPosition, OUT OutDirection);
    const FVector Offset = OutDirection.RotateVector(RandomDrift(Drift + CurrentSpread));
    OutEndPosition = OutStartPosition + (OutDirection.Vector() * MaxRange) + Offset;
    CurrentSpread += SpreadFactor;
}

bool AGun::CheckHit(FHitResult& OutHitResult, const FVector& StartPosition, const FVector& EndPosition) const
{
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);
    Params.AddIgnoredActor(Owner);
    return GetWorld()->LineTraceSingleByChannel(OUT OutHitResult, StartPosition, EndPosition, ECC_GameTraceChannel1, Params);
}

void AGun::ApplyDamage(const FHitResult& Hit, const FVector& Direction)
{
    AActor* HitActor = Hit.GetActor();
    if (HitActor)
    {
        const FPointDamageEvent DamageEvent(Damage, Hit, Direction, nullptr);
        HitActor->TakeDamage(Damage, DamageEvent, Controller, this);
    }
}

void AGun::MuzzleEffects() const
{
    if (MuzzleFlash)
    {
        UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, MuzzleSocketName);
    }
    if (MuzzleSound)
    {
        UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, MuzzleSocketName);
    }
}

void AGun::ImpactEffects(const FHitResult& Hit, const FRotator& Direction) const
{
    const UWorld* World = GetWorld();
    if (ImpactEffect)
    {
        UGameplayStatics::SpawnEmitterAtLocation(World, ImpactEffect, Hit.Location, Direction);
    }
    if (ImpactSound)
    {
        UGameplayStatics::PlaySoundAtLocation(World, ImpactSound, Hit.Location, Direction);
    }
}

float AGun::RandSign()
{
    return FMath::RandBool() ? 1.0f : -1.0f;
}

FVector2D AGun::RandomUnitVector()
{
    const float X = FMath::FRand();
    const float Y = FMath::Sqrt(1 - FMath::Square(X));
    return FVector2D(X * RandSign(), Y * RandSign());
}

FVector AGun::RandomDrift(const float MaxDrift)
{
    const FVector2D Offset = RandomUnitVector() * FMath::FRandRange(0.0f, MaxDrift);
    return FVector(0.0f, Offset.X, Offset.Y);
}
