// Copyright © Christophe Savard 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class ATankGameModeBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:	
    UHealthComponent();

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void TakeDamage(AActor* Damaged, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* Attacker);

private:
    float Health;
    ATankGameModeBase* GameMode;

    UPROPERTY(EditAnywhere)
    float MaxHealth = 100.0f;
};
