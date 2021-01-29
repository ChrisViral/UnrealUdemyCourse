// Copyright © Christophe Savard 2021

#include "PawnTank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

APawnTank::APawnTank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}


void APawnTank::BeginPlay()
{
    Super::BeginPlay();
}

void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APawnTank::CalculateMove);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APawnTank::CalculateTurn);
}

void APawnTank::Tick(const float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    AddActorLocalRotation(FQuat(Rotation * DeltaTime), true);
    AddActorLocalOffset(Direction * DeltaTime, true);
}

void APawnTank::CalculateMove(const float Value)
{
    Direction = FVector::ForwardVector * (Value * MoveSpeed);
}

void APawnTank::CalculateTurn(const float Value)
{
    Rotation = FRotator(0.0f, Value * TurnSpeed, 0.0f);
}
