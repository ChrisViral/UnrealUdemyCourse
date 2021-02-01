// Copyright © Christophe Savard 2021

#include "TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"

#define OUT

void ATankGameModeBase::BeginPlay()
{
    Super::BeginPlay();
 
    Player = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
    PlayerController = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

    TArray<AActor*> Turrets;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), OUT Turrets);
    TurretCount = Turrets.Num();

    StartGame();

    if (PlayerController)
    {
        PlayerController->SetPlayerEnabled(false);
        FTimerHandle PlayerEnableTimer;
        const FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerController, &APlayerControllerBase::SetPlayerEnabled, true);
        GetWorld()->GetTimerManager().SetTimer(OUT PlayerEnableTimer, PlayerEnableDelegate, StartDelay + 1.0f, false);
    }
}

void ATankGameModeBase::ActorDied(AActor* Killed)
{
    if (Killed == Player)
    {
        Player->OnDestroy();
        EndGame(false);

        if (PlayerController)
        {
            PlayerController->SetPlayerEnabled(false);
        }
    }
    else if (APawnTurret* Turret = Cast<APawnTurret>(Killed))
    {
        Turret->OnDestroy();
        if (--TurretCount == 0)
        {
            EndGame(true);
        }
    }
}

void ATankGameModeBase::StartGame()
{
    GameStart();
}

void ATankGameModeBase::EndGame(const bool bWon)
{
    GameOver(bWon);
}
