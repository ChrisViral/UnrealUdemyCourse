// Copyright © Christophe Savard 2021

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_LocateIfVisible.generated.h"

class AAIController;
class UBlackboardComponent;

UCLASS()
class SIMPLESHOOTER_API UBTService_LocateIfVisible : public UBTService_BlackboardBase
{
    GENERATED_BODY()

public:
    UBTService_LocateIfVisible();

protected:
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, const float DeltaTime) override;

private:
    bool bInitialized;
    bool bCanSeePlayer;
    AAIController* Controller;
    APawn* Player;
    UBlackboardComponent* Blackboard;

    bool Initialize(UBehaviorTreeComponent& OwnerComp);
};
