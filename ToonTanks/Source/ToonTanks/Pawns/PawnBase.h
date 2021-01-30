// Copyright © Christophe Savard 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

class UCapsuleComponent;
class AProjectileBase;

UCLASS(Abstract)
class TOONTANKS_API APawnBase : public APawn
{
    GENERATED_BODY()

public:
    APawnBase();

protected:
    virtual void LookAt(const FVector Target);

    virtual void Fire();

    virtual void OnDestroy();

private:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UCapsuleComponent* Capsule;
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* BaseMesh;
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* TurretMesh;
    UPROPERTY(VisibleAnywhere, Category = "Components")
    USceneComponent* ProjectileSpawn;
    UPROPERTY(EditAnywhere, Category = "Projectile")
    TSubclassOf<AProjectileBase> ProjectileClass;
};
