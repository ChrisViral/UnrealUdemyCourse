// Copyright © Christophe Savard 2021


#include "ShooterController.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"

void AShooterController::BeginPlay()
{
    Super::BeginPlay();

    HUD = CreateWidget(this, HUDType);
    if (HUD)
    {
        HUD->AddToViewport();
    }
}

void AShooterController::GameHasEnded(AActor* EndGameFocus, const bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    if (HUD)
    {
        HUD->RemoveFromViewport();
    }

    EndScreen = CreateWidget(this, bIsWinner ? WinScreenType : LoseScreenType);
    if (EndScreen)
    {
        EndScreen->AddToViewport();
    }

    GetWorldTimerManager().SetTimer(RestartTimer, this, &AShooterController::RestartLevel, RestartDelay);
}
