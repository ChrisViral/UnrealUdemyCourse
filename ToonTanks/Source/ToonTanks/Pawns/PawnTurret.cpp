// Copyright © Christophe Savard 2021

#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

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
    
    const bool bInRange = FVector::Dist(Player->GetActorLocation(), GetActorLocation()) <= FireRange;
    if (bInRange != bInFireRange)
    {
        bInFireRange = bInRange;
        FTimerManager* TimerManager = &GetWorld()->GetTimerManager();
        if (bInFireRange)
        {
            const float FireDelay = 1.0f / FireRate;
            TimerManager->SetTimer(FireRateTimer, this, &APawnTurret::FireRateTick, FireDelay, true, FireDelay / 2.0f);
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
