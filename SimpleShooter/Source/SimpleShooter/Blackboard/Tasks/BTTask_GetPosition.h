// Copyright © Christophe Savard 2021

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_GetPosition.generated.h"

UCLASS()
class SIMPLESHOOTER_API UBTTask_GetPosition : public UBTTask_BlackboardBase
{
    GENERATED_BODY()
        
public:
    UBTTask_GetPosition();

protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
