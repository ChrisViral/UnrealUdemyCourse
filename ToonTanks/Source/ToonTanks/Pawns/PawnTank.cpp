// Copyright © Christophe Savard 2021

#include "PawnTank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"

#define OUT

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

    PlayerController = Cast<APlayerController>(GetController());
}

void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APawnTank::CalculateMove);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APawnTank::CalculateTurn);
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &APawnTank::Fire);
}

void APawnTank::Tick(const float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    AddActorLocalRotation(FQuat(Rotation * DeltaTime), true);
    AddActorLocalOffset(Direction * DeltaTime, true);

    if (PlayerController)
    {
        FHitResult Hit;
        PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, OUT Hit);
        LookAt(Hit.ImpactPoint);
    }
}

void APawnTank::CalculateMove(const float Value)
{
    Direction = FVector::ForwardVector * (Value * MoveSpeed);
}

void APawnTank::CalculateTurn(const float Value)
{
    Rotation = FRotator(0.0f, Value * TurnSpeed, 0.0f);
}

void APawnTank::OnDestroy()
{
    Super::OnDestroy();

    bIsAlive = false;
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(ExplosionShake);
}
