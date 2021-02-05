// Copyright © Christophe Savard 2021

#include "BTService_LocateIfVisible.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_LocateIfVisible::UBTService_LocateIfVisible()
{
    NodeName = TEXT("Update If Visible");
}

void UBTService_LocateIfVisible::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, const float DeltaTime)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaTime);

    if (!Initialize(OwnerComp))
    {
        return;
    }

    const bool bIsVisible = Controller->LineOfSightTo(Player);
    if (bIsVisible != bCanSeePlayer)
    {
        bCanSeePlayer = bIsVisible;
        if (!bCanSeePlayer)
        {
            Blackboard->ClearValue(GetSelectedBlackboardKey());
            return;
        }
    }

    if (bCanSeePlayer)
    {
        Blackboard->SetValueAsObject(GetSelectedBlackboardKey(), Player);
    }
}

bool UBTService_LocateIfVisible::Initialize(UBehaviorTreeComponent& OwnerComp)
{
    if (!bInitialized)
    {
        bInitialized = true;
        Controller = OwnerComp.GetAIOwner();
        Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        Blackboard = OwnerComp.GetBlackboardComponent();
    }

    return Controller && Player && Blackboard;
}
