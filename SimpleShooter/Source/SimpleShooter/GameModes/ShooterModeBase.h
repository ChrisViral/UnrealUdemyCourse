// Copyright © Christophe Savard 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterModeBase.generated.h"

UCLASS(Abstract)
class SIMPLESHOOTER_API AShooterModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    virtual void PawnKilled(APawn* KilledPawn) PURE_VIRTUAL(AShooterModeBase::PawnKilled);
};
