// Copyright © Christophe Savard 2021

#pragma once

#include "CoreMinimal.h"
#include "SimpleShooter/GameModes/ShooterModeBase.h"
#include "KillEmAllMode.generated.h"

UCLASS()
class SIMPLESHOOTER_API AKillEmAllMode : public AShooterModeBase
{
    GENERATED_BODY()

public:
    virtual void PawnKilled(APawn* KilledPawn) override;

private:
    void GameOver(const bool bWon) const;
    bool AllAIDead() const;
};
