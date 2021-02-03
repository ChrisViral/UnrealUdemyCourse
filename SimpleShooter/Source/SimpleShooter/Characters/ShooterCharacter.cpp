// Copyright © Christophe Savard 2021

#include "ShooterCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "SimpleShooter/Actors/Gun.h"

AShooterCharacter::AShooterCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

void AShooterCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    USkeletalMeshComponent* BodyMesh = GetMesh();
    BodyMesh->HideBoneByName(WeaponBoneName, PBO_None);

    Gun = GetWorld()->SpawnActor<AGun>(GunType);
    Gun->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform, WeaponSocketName);
    Gun->SetOwner(this);

    Health = MaxHealth;
}

void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInput)
{
    Super::SetupPlayerInputComponent(PlayerInput);

    PlayerInput->BindAction(TEXT("Jump"), IE_Pressed, this, &AShooterCharacter::Jump);
    PlayerInput->BindAction(TEXT("Jump"), IE_Released, this, &AShooterCharacter::StopJumping);

    PlayerInput->BindAction(TEXT("Fire"), IE_Pressed, this, &AShooterCharacter::Fire);

    PlayerInput->BindAxis(TEXT("MoveForwards"), this, &AShooterCharacter::MoveForwards);
    PlayerInput->BindAxis(TEXT("MoveSideways"), this, &AShooterCharacter::MoveSideways);

    PlayerInput->BindAxis(TEXT("LookX"), this, &AShooterCharacter::AddControllerYawInput);
    PlayerInput->BindAxis(TEXT("LookY"), this, &AShooterCharacter::AddControllerPitchInput);

    PlayerInput->BindAxis(TEXT("LookXGamepad"), this, &AShooterCharacter::LookXGamepad);
    PlayerInput->BindAxis(TEXT("LookYGamepad"), this, &AShooterCharacter::LookYGamepad);
}

void AShooterCharacter::MoveForwards(const float Axis)
{
    AddMovementInput(GetActorForwardVector() * Axis);
}

void AShooterCharacter::MoveSideways(const float Axis)
{
    AddMovementInput(GetActorRightVector() * Axis);
}

void AShooterCharacter::LookXGamepad(const float Axis)
{
    AddControllerYawInput(Axis * ControllerLookRate.X * GetWorld()->DeltaTimeSeconds);
}

void AShooterCharacter::LookYGamepad(const float Axis)
{
    AddControllerPitchInput(Axis * ControllerLookRate.Y * GetWorld()->DeltaTimeSeconds);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AShooterCharacter::Fire()
{
    if (Gun)
    {
        Gun->PullTrigger();
    }
}

float AShooterCharacter::TakeDamage(const float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    const float Applied = FMath::Min(Health, Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser));
    Health -= Applied;

    UE_LOG(LogTemp, Warning, TEXT("%s health is %f"), *GetName(), Health);

    return Applied;
}
