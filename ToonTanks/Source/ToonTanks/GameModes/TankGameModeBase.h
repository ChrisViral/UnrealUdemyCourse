// Copyright © Christophe Savard 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class APawnTank;
class APawnTurret;
class APlayerControllerBase;

UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    void ActorDied(AActor* Killed);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
    int32 StartDelay = 3;

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintImplementableEvent)
    void GameStart();
    UFUNCTION(BlueprintImplementableEvent)
    void GameOver(const bool bWon);

private:

    APawnTank* Player;
    APlayerControllerBase* PlayerController;
    int32 TurretCount = 0;

    void StartGame();
    void EndGame(const bool bWon);
};
