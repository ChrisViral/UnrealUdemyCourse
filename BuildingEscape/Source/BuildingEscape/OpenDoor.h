// Copyright © Christophe Savard 2021

#pragma once

#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
    GENERATED_BODY()

public:	
    // Sets default values for this component's properties
    UOpenDoor();

    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;
    
private:
    const float Tolerance = 1E-2f;
    
    UPROPERTY(EditAnywhere)
    float OpenAngle = 90.0f;
    UPROPERTY(EditAnywhere)
    float CloseDelay = 1.0f;
    UPROPERTY(EditAnywhere)
    float OpenTime = 5.0f;
    UPROPERTY(EditAnywhere)
    float CloseTime = 3.0f;
    UPROPERTY(EditAnywhere)
    float OpenExp = 2.0f;
    UPROPERTY(EditAnywhere)
    float TriggerMass = 10.0f;
    UPROPERTY(EditAnywhere)
    ATriggerVolume* DoorTrigger = nullptr;
    UPROPERTY()
    UAudioComponent* DoorSound = nullptr;

    bool bMustOpen = false;
    bool bIsOpening = false;
    float ClosedAngle = 0.0f;
    float OpenedAngle = 0.0f;
    float DoorDelayTime = 0.0f;
    float TargetTime = 0.0f;
    float TargetAngle = 0.0f;
    float Elapsed = 0.0f;
    float CurrentMass = 0.0f;
    

    inline bool Validate() const;

    inline bool IsTriggered() const;

    void PlayDoorSound() const;

    UFUNCTION()
    void OnActorEnter(AActor* OverlappedActor, AActor* OtherActor);
    
    UFUNCTION()
    void OnActorExit(AActor* OverlappedActor, AActor* OtherActor);
};

inline bool UOpenDoor::Validate() const
{
    return DoorTrigger != nullptr;
}

inline bool UOpenDoor::IsTriggered() const
{
    return CurrentMass >= TriggerMass;
}