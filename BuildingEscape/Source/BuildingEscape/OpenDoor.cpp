// Copyright © Christophe Savard 2021

#include "OpenDoor.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"


UOpenDoor::UOpenDoor()
{
    PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
    Super::BeginPlay();
    
    ClosedAngle = GetOwner()->GetActorRotation().Yaw;
    OpenedAngle = ClosedAngle + OpenAngle;
    DoorSound = GetOwner()->FindComponentByClass<UAudioComponent>();

    if (!DoorSound)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s has no door sound object"), *GetOwner()->GetName());
    }

    if (!DoorTrigger)
    {
        UE_LOG(LogTemp, Error, TEXT("%s has no door trigger"), *GetOwner()->GetName())
    }
    else
    {
        DoorTrigger->OnActorBeginOverlap.AddDynamic(this, &UOpenDoor::OnActorEnter);
        DoorTrigger->OnActorEndOverlap.AddDynamic(this, &UOpenDoor::OnActorExit);
    }
}


// Called every frame
void UOpenDoor::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!Validate())
    {
        return;
    }

    if (bIsOpening && GetWorld()->GetTimeSeconds() >= DoorDelayTime)
    {
        Elapsed += DeltaTime;
        AActor* Owner = GetOwner();
        FRotator Rotation = Owner->GetActorRotation();
        Rotation.Yaw = FMath::InterpEaseInOut(Rotation.Yaw, TargetAngle, Elapsed / TargetTime, OpenExp);
        
        if (FMath::Abs(Rotation.Yaw - TargetAngle) < Tolerance)
        {
            Rotation.Yaw = TargetAngle;
            bIsOpening = false;
            if (!bMustOpen)
            {
                PlayDoorSound();
            }
        }
        
        Owner->SetActorRotation(Rotation);
    }
}

void UOpenDoor::PlayDoorSound() const
{
    if (DoorSound)
    {
        DoorSound->Play();
    }
}


void UOpenDoor::OnActorEnter(AActor* OverlappedActor, AActor* OtherActor)
{
    CurrentMass += OtherActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
    if (IsTriggered() && !bMustOpen)
    {
        bMustOpen = true;
        TargetAngle = OpenedAngle;
        TargetTime = OpenTime;
        Elapsed = 0.0f;

        if (!bIsOpening)
        {
            PlayDoorSound();
        }
        bIsOpening = true;
    }
}

void UOpenDoor::OnActorExit(AActor* OverlappedActor, AActor* OtherActor)
{
    CurrentMass -= OtherActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
    if (!IsTriggered() && bMustOpen)
    {
        bMustOpen = false;
        TargetAngle = ClosedAngle;
        TargetTime = CloseTime;
        Elapsed = 0.0f;

        if (!bIsOpening)
        {
            DoorDelayTime = GetWorld()->GetTimeSeconds() + CloseDelay;
        }
        bIsOpening = true;
    }
}
