// Copyright © Christophe Savard 2021

#include "ShooterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"

AShooterAIController::AShooterAIController()
{
    PrimaryActorTick.bCanEverTick = true;
}

bool AShooterAIController::IsAlive() const
{
    return ShooterCharacter && ShooterCharacter->IsAlive();
}

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();
    
    if (!Behaviour)
    {
        UE_LOG(LogTemp, Warning, TEXT("Behaviour tree not found!"));
        return;
    }

    ShooterCharacter = Cast<AShooterCharacter>(GetPawn());
    RunBehaviorTree(Behaviour);
}
