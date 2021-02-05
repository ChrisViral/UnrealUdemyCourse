// Copyright © Christophe Savard 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class AShooterCharacter;
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
    void ReleaseTrigger();
    void SwitchType();
    void Reload();
    inline int32 GetClip() const;
    inline bool CanFire() const;
    inline bool IsReloading() const;

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
    UPROPERTY(EditAnywhere, Category="Recoil")
    float VerticalRecoil = 1.0f;
    UPROPERTY(EditAnywhere, Category="Recoil")
    float RecoilVariance = 0.1f;
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
    UPROPERTY(EditAnywhere, Category="Firing")
    TArray<TEnumAsByte<EFiringType>> FiringTypes = TArray<TEnumAsByte<EFiringType>>({ SemiAuto, Automatic, Burst });
    UPROPERTY(EditAnywhere, Category="Firing|Semi-Auto")
    float SemiAutoFireRate = 2.0f;
    UPROPERTY(EditAnywhere, Category="Firing|Automatic")
    float AutoFireRate = 10.0f;
    UPROPERTY(EditAnywhere, Category="Firing|Burst")
    int32 BurstSize = 3;
    UPROPERTY(EditAnywhere, Category="Firing|Burst")
    float BurstRate = 15.0f;
    UPROPERTY(EditAnywhere, Category="Firing|Burst")
    float BurstFireRate = 2.0f;
    UPROPERTY(EditAnywhere, Category="Magazine")
    int32 ClipSize = 20;
    UPROPERTY(EditAnywhere, Category="Magazine")
    float ReloadTime = 3.0f;


    bool bInitialized;
    bool bTriggerHeld;
    bool bCanFire = true;
    bool bInBurst;
    bool bReloading;
    FTimerHandle FireRateTimer;
    FTimerHandle BurstTimer;
    FTimerHandle ReloadTimer;
    AShooterCharacter* Owner;
    AController* Controller;
    FTransform Transform;
    float CurrentSpread;
    float MinRecoil;
    float MaxRecoil;
    float FireDelay;
    float BurstDelay;
    float BurstTime;
    int32 BurstCount;
    int32 Clip;
    int32 FiringTypeIndex = -1;
    TEnumAsByte<EFiringType> FiringType;

    void Fire();
    bool Initialize();
    void GetViewpoint(FVector& OutStartPosition, FVector& OutEndPosition, FRotator& OutDirection);
    bool CheckHit(FHitResult& OutHitResult, const FVector& StartPosition, const FVector& EndPosition) const;
    void ApplyDamage(const FHitResult& Hit, const FVector& Direction);
    void MuzzleEffects() const;
    void ImpactEffects(const FHitResult& Hit, const FRotator& Direction) const;
    void WaitFireRate();
    void FinishReload();

    static float RandSign();
    static FVector2D RandomUnitVector();
    static FVector RandomDrift(const float MaxDrift);
};

inline int32 AGun::GetClip() const
{
    return Clip;
}

inline bool AGun::CanFire() const
{
    return bCanFire && !bReloading && Clip > 0;
}

inline bool AGun::IsReloading() const
{
    return bReloading;
}
