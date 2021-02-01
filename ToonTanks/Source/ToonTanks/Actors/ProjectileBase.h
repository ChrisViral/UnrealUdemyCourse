// Copyright © Christophe Savard 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UParticleSystem;
class UParticleSystemComponent;
class UProjectileMovementComponent;

UCLASS()
class TOONTANKS_API AProjectileBase : public AActor
{
    GENERATED_BODY()
    
public:	
    AProjectileBase();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UProjectileMovementComponent* ProjectileMovement;
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* ProjectileMesh;
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UParticleSystemComponent* TrailEffect;
    UPROPERTY(EditAnywhere, Category = "Effects")
    UParticleSystem* HitEffect;
    UPROPERTY(EditAnywhere, Category = "Effects")
    USoundBase* HitSound;
    UPROPERTY(EditAnywhere, Category = "Effects")
    USoundBase* LaunchSound;
    UPROPERTY(EditAnywhere, Category = "Effects")
    TSubclassOf<UCameraShake> HitShake;
    UPROPERTY(EditAnywhere, Category = "Damage")
    TSubclassOf<UDamageType> DamageType;
    UPROPERTY(EditAnywhere, Category = "Damage")
    float Damage = 50.0f;
    UPROPERTY(EditAnywhere, Category = "Movement")
    float Speed = 1300.0f;
    UPROPERTY(EditAnywhere, Category = "Movement")
    float Lifespan = 3.0f;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* Other, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
