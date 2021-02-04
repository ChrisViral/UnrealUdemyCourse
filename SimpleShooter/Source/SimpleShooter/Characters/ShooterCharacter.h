// Copyright © Christophe Savard 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class UCameraComponent;
class AGun;
class USpringArmComponent;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AShooterCharacter();

    UFUNCTION(BlueprintPure)
    inline bool IsAlive() const;
    
    void Fire();
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInput) override;
    virtual float TakeDamage(const float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere, Category="Components")
    USpringArmComponent* SpringArm;
    UPROPERTY(VisibleAnywhere, Category="Components")
    UCameraComponent* Camera;
    UPROPERTY(EditAnywhere, Category="Movement")
    FVector2D ControllerLookRate = FVector2D(100.0f, 50.0f);
    UPROPERTY(EditDefaultsOnly, Category="Gun")
    TSubclassOf<AGun> GunType;
    UPROPERTY(EditDefaultsOnly, Category="Gun")
    FName WeaponBoneName;
    UPROPERTY(EditDefaultsOnly, Category="Gun")
    FName WeaponSocketName;
    UPROPERTY(EditDefaultsOnly, Category="Health")
    float MaxHealth = 100.0f;
    UPROPERTY(VisibleAnywhere, Category="Health")
    float Health;

    AGun* Gun;

    void MoveForwards(const float Axis);
    void MoveSideways(const float Axis);
    void LookXGamepad(const float Axis);
    void LookYGamepad(const float Axis);
};

inline bool AShooterCharacter::IsAlive() const
{
    return Health > 0.0f;
}
