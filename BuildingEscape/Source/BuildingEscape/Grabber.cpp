// Copyright © Christophe Savard 2021

#include "Grabber.h"
#include "Components/PrimitiveComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT

UGrabber::UGrabber()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay()
{
    Super::BeginPlay();

    Player = GetWorld()->GetFirstPlayerController();
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    Input = GetOwner()->FindComponentByClass<UInputComponent>();
    
    if (!PhysicsHandle)
    {
        UE_LOG(LogTemp, Error, TEXT("No PhysicsHandle found on Grabber %s!"), *GetOwner()->GetName());
    }

    if (!Input)
    {
        UE_LOG(LogTemp, Error, TEXT("No InputComponent found on Grabber %s!"), *GetOwner()->GetName());
    }
    else
    {
        Input->BindAction(GrabMapping, IE_Pressed, this, &UGrabber::Grab);
        Input->BindAction(GrabMapping, IE_Released, this, &UGrabber::Release);
    }
}

void UGrabber::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    FRotator Rotation;
    Player->GetPlayerViewPoint(OUT RayStart, OUT Rotation);
    RayEnd = RayStart + Rotation.Vector() * Reach;
    DrawDebugLine(GetWorld(), RayStart, RayEnd, FColor::Red, false, -1.0f, 0, 2.0f);

    if (Grabbed)
    {
        PhysicsHandle->SetTargetLocationAndRotation(RayEnd, Rotation);
    }
} 

void UGrabber::Grab()
{
    if (!Validate() || Grabbed)
    {
        return;
    }
    
    FHitResult Hit;
    GetWorld()->LineTraceSingleByObjectType(OUT Hit, RayStart, RayEnd,
                                            FCollisionObjectQueryParams(ECC_PhysicsBody),
                                            FCollisionQueryParams(FName(), false, GetOwner()));

    AActor* HitActor = Hit.GetActor();
    if (HitActor)
    {
        Grabbed = Hit.GetComponent();
        PhysicsHandle->GrabComponentAtLocation(Grabbed, NAME_None, HitActor->GetActorLocation());
    }
}

void UGrabber::Release()
{
    if (!Validate() || !Grabbed)
    {
        return;
    }

    Grabbed = nullptr;
    PhysicsHandle->ReleaseComponent();
}
