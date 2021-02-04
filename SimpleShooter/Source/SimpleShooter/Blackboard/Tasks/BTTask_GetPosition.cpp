// Copyright © Christophe Savard 2021


#include "BTTask_GetPosition.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_GetPosition::UBTTask_GetPosition()
{
    NodeName = TEXT("Get Position");
}

EBTNodeResult::Type UBTTask_GetPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController* Controller = OwnerComp.GetAIOwner();
    if (!Controller)
    {
        return EBTNodeResult::Failed;
    }

    APawn* Owner = Controller->GetPawn();
    if (!Owner)
    {
        return EBTNodeResult::Failed;
    }

    OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Owner->GetActorLocation());
    return EBTNodeResult::Succeeded;
}
