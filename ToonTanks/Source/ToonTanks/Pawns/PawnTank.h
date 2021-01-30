// Copyright © Christophe Savard 2021

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTank.generated.h"

class UCameraComponent;
class USpringArmComponent;
class APlayerController;

UCLASS()
class TOONTANKS_API APawnTank : public APawnBase
{
    GENERATED_BODY()

public:
    APawnTank();

    virtual void Tick(const float DeltaTime) override;
    
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UCameraComponent* Camera;
    UPROPERTY(VisibleAnywhere, Category = "Components")
    USpringArmComponent* SpringArm;
    UPROPERTY(EditAnywhere, Category = "Movement")
    float MoveSpeed = 100.0f;
    UPROPERTY(EditAnywhere, Category = "Movement")
    float TurnSpeed = 100.0f;

    FVector Direction;
    FRotator Rotation;
    APlayerController* PlayerController;

    void CalculateMove(const float Value);
    void CalculateTurn(const float Value);
    virtual void OnDestroy() override;
};
