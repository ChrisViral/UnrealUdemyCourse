// Copyright © Christophe Savard 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

class UCapsuleComponent;
class UHealthComponent;
class UParticleSystem;
class AProjectileBase;

UCLASS(Abstract)
class TOONTANKS_API APawnBase : public APawn
{
    GENERATED_BODY()

public:
    APawnBase();

    virtual void OnDestroy();

protected:
    virtual void LookAt(const FVector Target);

    virtual void Fire();

private:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UCapsuleComponent* Capsule;
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* BaseMesh;
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* TurretMesh;
    UPROPERTY(VisibleAnywhere, Category = "Components")
    USceneComponent* ProjectileSpawn;
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UHealthComponent* Health;
    UPROPERTY(EditAnywhere, Category = "Projectile")
    TSubclassOf<AProjectileBase> ProjectileClass;
    UPROPERTY(EditAnywhere, Category = "Effects")
    UParticleSystem* ExplosionEffect;
    UPROPERTY(EditAnywhere, Category = "Effects")
    USoundBase* ExplosionSound;
};
