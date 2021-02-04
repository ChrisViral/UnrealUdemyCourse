// Copyright © Christophe Savard 2021

#include "BTService_PlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_PlayerLocation::UBTService_PlayerLocation()
{
    NodeName = TEXT("Update Player Position");
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, const float DeltaTime)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaTime);

    if (Initialize(OwnerComp))
    {
        Blackboard->SetValueAsVector(GetSelectedBlackboardKey(), Player->GetActorLocation());
    }
}

bool UBTService_PlayerLocation::Initialize(UBehaviorTreeComponent& OwnerComp)
{
    if (!bInitialized)
    {
        bInitialized = true;
        Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        Blackboard = OwnerComp.GetBlackboardComponent();
    }

    return Player && Blackboard;
}
