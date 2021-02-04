// Copyright © Christophe Savard 2021

#include "KillEmAllMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "SimpleShooter/Controllers/ShooterAIController.h"

void AKillEmAllMode::PawnKilled(APawn* KilledPawn)
{
    UE_LOG(LogTemp, Warning, TEXT("%s was killed!"), *KilledPawn->GetName());

    APlayerController* Controller = Cast<APlayerController>(KilledPawn->GetController());
    if (Controller)
    {
        GameOver(false);
    }
    else if (AllAIDead())
    {
        GameOver(true);
    }
}

void AKillEmAllMode::GameOver(const bool bWon) const
{
    for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        Controller->GameHasEnded(Controller->GetPawn(), Controller->IsPlayerController() == bWon);
    }
}

bool AKillEmAllMode::AllAIDead() const
{
    for (AShooterAIController* AIController : TActorRange<AShooterAIController>(GetWorld()))
    {
        if (AIController->IsAlive())
        {
            return false;
        }
    }

    return true;
}
