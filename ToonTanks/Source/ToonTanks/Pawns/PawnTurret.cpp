// Copyright © Christophe Savard 2021

#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

#define OUT

void APawnTurret::BeginPlay()
{
    Super::BeginPlay();
    Player = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void APawnTurret::Tick(const float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!Player)
    {
        return;
    }

    if (!Player->GetIsAlive())
    {
        if (bInFireRange)
        {
            GetWorld()->GetTimerManager().ClearTimer(FireRateTimer);
        }

        bInFireRange = false;
        SetActorTickEnabled(false);
        return;
    }
    
    const bool bInRange = FVector::Dist(Player->GetActorLocation(), GetActorLocation()) <= FireRange;
    if (bInRange != bInFireRange)
    {
        bInFireRange = bInRange;
        FTimerManager* TimerManager = &GetWorld()->GetTimerManager();
        if (bInFireRange)
        {
            const float FireDelay = 1.0f / FireRate;
            TimerManager->SetTimer(OUT FireRateTimer, this, &APawnTurret::FireRateTick, FireDelay, true, FireDelay / 2.0f);
        }
        else
        {
            TimerManager->ClearTimer(FireRateTimer);
        }
    }

    if (bInFireRange)
    {
        LookAt(Player->GetActorLocation());
    }
}

void APawnTurret::FireRateTick()
{
    if (Player && bInFireRange)
    {
        Fire();
    }
}

void APawnTurret::OnDestroy()
{
    Super::OnDestroy();

    Destroy();
}

