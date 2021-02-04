// Copyright © Christophe Savard 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"


UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
    GENERATED_BODY()

public:
    AGun();
    
    void PullTrigger();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere, Category="Components")
    USceneComponent* Root;
    UPROPERTY(VisibleAnywhere, Category="Components")
    USkeletalMeshComponent*  Mesh;
    UPROPERTY(EditAnywhere, Category="Bullet")
    float MaxRange = 10000.0f;
    UPROPERTY(EditAnywhere, Category="Bullet")
    float Damage = 10.0f;
    UPROPERTY(EditDefaultsOnly, Category="Effects")
    FName MuzzleSocketName;
    UPROPERTY(EditAnywhere, Category="Effects")
    UParticleSystem* MuzzleFlash;
    UPROPERTY(EditAnywhere, Category="Effects")
    UParticleSystem* ImpactEffect;
};
