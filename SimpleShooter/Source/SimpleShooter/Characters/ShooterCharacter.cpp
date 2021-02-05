// Copyright © Christophe Savard 2021

#include "ShooterCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "SimpleShooter/Actors/Gun.h"
#include "SimpleShooter/GameModes/ShooterModeBase.h"

AShooterCharacter::AShooterCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

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
    PlayerInput->BindAction(TEXT("Fire"), IE_Released, this, &AShooterCharacter::StopFiring);

    PlayerInput->BindAction(TEXT("Switch"), IE_Pressed, this, &AShooterCharacter::SwitchWeaponMode);

    PlayerInput->BindAxis(TEXT("MoveForwards"), this, &AShooterCharacter::MoveForwards);
    PlayerInput->BindAxis(TEXT("MoveSideways"), this, &AShooterCharacter::MoveSideways);

    PlayerInput->BindAxis(TEXT("LookX"), this, &AShooterCharacter::AddControllerYawInput);
    PlayerInput->BindAxis(TEXT("LookY"), this, &AShooterCharacter::AddControllerPitchInput);

    PlayerInput->BindAxis(TEXT("LookXGamepad"), this, &AShooterCharacter::LookXGamepad);
    PlayerInput->BindAxis(TEXT("LookYGamepad"), this, &AShooterCharacter::LookYGamepad);
}

void AShooterCharacter::MoveForwards(const float Axis)
{
    if (IsAlive())
    {
        AddMovementInput(GetActorForwardVector() * Axis);
    }
}

void AShooterCharacter::MoveSideways(const float Axis)
{
    if (IsAlive())
    {
        AddMovementInput(GetActorRightVector() * Axis);
    }
}

void AShooterCharacter::LookXGamepad(const float Axis)
{
    if (IsAlive())
    {
        AddControllerYawInput(Axis * ControllerLookRate.X * GetWorld()->DeltaTimeSeconds);
    }
}

void AShooterCharacter::LookYGamepad(const float Axis)
{
    if (IsAlive())
    {
        AddControllerPitchInput(Axis * ControllerLookRate.Y * GetWorld()->DeltaTimeSeconds);
    }
}

//ReSharper disable once CppMemberFunctionMayBeConst
void AShooterCharacter::SwitchWeaponMode()
{
    if (IsAlive())
    {
        Gun->SwitchType();
    }
}

//ReSharper disable once CppMemberFunctionMayBeConst
void AShooterCharacter::Fire()
{
    if (Gun && IsAlive())
    {
        Gun->PullTrigger();
    }
}

//ReSharper disable once CppMemberFunctionMayBeConst
void AShooterCharacter::StopFiring()
{
    if (Gun && IsAlive())
    {
        Gun->ReleaseTrigger();
    }
}

void AShooterCharacter::ApplyRecoil(const float Recoil)
{
    if (IsAlive())
    {
        AddControllerPitchInput(-Recoil * GetWorld()->DeltaTimeSeconds);
    }
}


float AShooterCharacter::TakeDamage(const float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    if (!IsAlive())
    {
        return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
    }

    const float Applied = FMath::Min(Health, Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser));
    Health -= Applied;

    if (!IsAlive())
    {
        if (Gun)
        {
            Gun->ReleaseTrigger();
        }

        UCapsuleComponent* Capsule = GetCapsuleComponent();
        if (Capsule)
        {
            Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        }

        AShooterModeBase* GameMode = GetWorld()->GetAuthGameMode<AShooterModeBase>();
        if (GameMode)
        {
            GameMode->PawnKilled(this);
        }

        //Detach at the end
        DetachFromControllerPendingDestroy();
    }

    return Applied;
}
