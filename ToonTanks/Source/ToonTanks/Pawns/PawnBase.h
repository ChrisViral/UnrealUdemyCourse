// Copyright © Christophe Savard 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

class UCapsuleComponent;

UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
    GENERATED_BODY()

public:
    APawnBase();

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UCapsuleComponent* Capsule;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* BaseMesh;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* TurretMesh;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    USceneComponent* ProjectileSpawn;
};
