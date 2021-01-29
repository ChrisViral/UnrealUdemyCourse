// Copyright © Christophe Savard 2021

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTank.generated.h"

class UCameraComponent;
class USpringArmComponent;

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
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UCameraComponent* Camera;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    USpringArmComponent* SpringArm;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float MoveSpeed = 100.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float TurnSpeed = 100.0f;

    FVector Direction;
    FRotator Rotation;

    void CalculateMove(const float Value);
    void CalculateTurn(const float Value);
};
