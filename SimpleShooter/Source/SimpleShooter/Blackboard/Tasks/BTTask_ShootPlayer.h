// Copyright © Christophe Savard 2021

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ShootPlayer.generated.h"

UCLASS()
class SIMPLESHOOTER_API UBTTask_ShootPlayer : public UBTTaskNode
{
    GENERATED_BODY()
        
public:
    UBTTask_ShootPlayer();

protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
