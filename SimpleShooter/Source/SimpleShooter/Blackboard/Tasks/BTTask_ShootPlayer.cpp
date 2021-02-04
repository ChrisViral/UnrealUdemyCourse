// Copyright © Christophe Savard 2021

#include "BTTask_ShootPlayer.h"
#include "AIController.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"

UBTTask_ShootPlayer::UBTTask_ShootPlayer()
{
    NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_ShootPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController* Controller = OwnerComp.GetAIOwner();
    if (!Controller)
    {
        return EBTNodeResult::Failed;
    }


    AShooterCharacter* Character = Cast<AShooterCharacter>(Controller->GetPawn());
    if (!Character)
    {
        return EBTNodeResult::Failed;
    }

    Character->Fire();
    return EBTNodeResult::Succeeded;
}
