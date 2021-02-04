// Copyright © Christophe Savard 2021

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

UCLASS()
class SIMPLESHOOTER_API AShooterAIController : public AAIController
{
    GENERATED_BODY()

public:
    AShooterAIController();

    bool IsAlive() const;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="AI")
    UBehaviorTree* Behaviour;
};
