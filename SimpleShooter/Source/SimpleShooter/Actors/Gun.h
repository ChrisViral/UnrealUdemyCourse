// Copyright © Christophe Savard 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class USoundBase;

UENUM()
enum EFiringType
{
    SemiAuto,
    Automatic,
    Burst
};

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
    GENERATED_BODY()

public:
    AGun();
    
    void PullTrigger();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(const float DeltaTime) override;

private:
    UPROPERTY(VisibleAnywhere, Category="Components")
    USceneComponent* Root;
    UPROPERTY(VisibleAnywhere, Category="Components")
    USkeletalMeshComponent*  Mesh;
    UPROPERTY(EditAnywhere, Category="Bullet")
    float MaxRange = 10000.0f;
    UPROPERTY(EditAnywhere, Category="Bullet")
    float Damage = 10.0f;
    UPROPERTY(EditAnywhere, Category="Spread")
    float Drift = 0.1f;
    UPROPERTY(EditAnywhere, Category="Spread")
    float SpreadFactor = 5.0f;
    UPROPERTY(EditAnywhere, Category="Spread")
    float RecoverFactor = 0.5f;
    UPROPERTY(EditDefaultsOnly, Category="Muzzle Effect")
    FName MuzzleSocketName;
    UPROPERTY(EditAnywhere, Category="Muzzle Effect")
    UParticleSystem* MuzzleFlash;
    UPROPERTY(EditAnywhere, Category="Muzzle Effect")
    USoundBase* MuzzleSound;
    UPROPERTY(EditAnywhere, Category="Impact Effect")
    UParticleSystem* ImpactEffect;
    UPROPERTY(EditAnywhere, Category="Impact Effect")
    USoundBase* ImpactSound;
    UPROPERTY(EditAnywhere, Category="FireRate")
    TEnumAsByte<EFiringType> FiringType = SemiAuto;
    UPROPERTY(EditAnywhere, Category="FireRate")
    float FireRate = 1.0f;
    UPROPERTY(EditAnywhere, Category="FireRate", AdvancedDisplay)
    int BurstSize = 3;
    UPROPERTY(EditAnywhere, Category="FireRate", AdvancedDisplay)
    float BurstRate = 0.2f;

    bool bInitialized;
    APawn* Owner;
    AController* Controller;
    FTransform Transform;
    float CurrentSpread;

    bool Initialize();
    void GetViewpoint(FVector& OutStartPosition, FVector& OutEndPosition, FRotator& OutDirection);
    bool CheckHit(FHitResult& OutHitResult, const FVector& StartPosition, const FVector& EndPosition) const;
    void ApplyDamage(const FHitResult& Hit, const FVector& Direction);
    void MuzzleEffects() const;
    void ImpactEffects(const FHitResult& Hit, const FRotator& Direction) const;

    static float RandSign();
    static FVector2D RandomUnitVector();
    static FVector RandomDrift(const float MaxDrift);
};
