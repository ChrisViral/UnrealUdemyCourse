// Copyright © Christophe Savard 2021

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

class APawnTank;

UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()

public:
    virtual void Tick(const float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "Combat")
    float FireRate = 1.0f;
    UPROPERTY(EditAnywhere, Category = "Combat")
    float FireRange = 500.0f;

    FTimerHandle FireRateTimer;
    APawnTank* Player;
    bool bInFireRange = false;

    void FireRateTick();
};
