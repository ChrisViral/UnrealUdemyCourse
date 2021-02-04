// Copyright © Christophe Savard 2021

#include "BTTask_ClearValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearValue::UBTTask_ClearValue()
{
    NodeName = TEXT("Clear Value");
}

EBTNodeResult::Type UBTTask_ClearValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    return EBTNodeResult::Succeeded;
}
