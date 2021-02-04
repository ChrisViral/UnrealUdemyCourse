// Copyright © Christophe Savard 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterController.generated.h"

class UUserWidget;

UCLASS()
class SIMPLESHOOTER_API AShooterController : public APlayerController
{
    GENERATED_BODY()

public:
    virtual void GameHasEnded(AActor* EndGameFocus = nullptr, const bool bIsWinner = false) override;

private:
    UPROPERTY(EditAnywhere, Category="Endgame")
    float RestartDelay = 3.0f;
    UPROPERTY(EditAnywhere, Category="Endgame")
    TSubclassOf<UUserWidget> WinScreenType;
    UPROPERTY(EditAnywhere, Category="Endgame")
    TSubclassOf<UUserWidget> LoseScreenType;

    FTimerHandle RestartTimer;
    UUserWidget* EndScreen;
};
