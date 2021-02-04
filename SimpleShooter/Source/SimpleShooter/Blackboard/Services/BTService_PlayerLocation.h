// Copyright © Christophe Savard 2021

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PlayerLocation.generated.h"

class UBlackboardComponent;

UCLASS()
class SIMPLESHOOTER_API UBTService_PlayerLocation : public UBTService_BlackboardBase
{
    GENERATED_BODY()

public:
    UBTService_PlayerLocation();

protected:
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, const float DeltaTime) override;

private:
    bool bInitialized;
    APawn* Player;
    UBlackboardComponent* Blackboard;

    bool Initialize(UBehaviorTreeComponent& OwnerComp);
};
