// Copyright © Christophe Savard 2021

#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/GameModes/TankGameModeBase.h"

UHealthComponent::UHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    Health = MaxHealth;
    GameMode = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
    GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* Damaged, const float Damage, const UDamageType* DamageType, AController* Instigator, AActor* Attacker)
{
    if (Health <= 0.0f || Damage == 0.0f)
    {
        return;
    }

    Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
    if (Health <= 0.0f && GameMode)
    {
        if (GameMode)
        {
            GameMode->ActorDied(GetOwner());
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Health component on %s has no reference to the GameMode"), *GetOwner()->GetName())
        }
    }
}
