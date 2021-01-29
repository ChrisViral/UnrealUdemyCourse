// Copyright © Christophe Savard 2021

#pragma once

#include "Components/InputComponent.h"
#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
    GENERATED_BODY()

public:	
    UGrabber();
    
    virtual void TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere)
    float Reach = 150.0f;
    UPROPERTY(EditAnywhere)
    FName GrabMapping = TEXT("Grab");
    UPROPERTY()
    UPhysicsHandleComponent* PhysicsHandle = nullptr;
    UPROPERTY()
    UInputComponent* Input = nullptr;
    UPROPERTY()
    UPrimitiveComponent* Grabbed = nullptr;

    FVector RayStart;
    FVector RayEnd;
    APlayerController* Player = nullptr;

    void Grab();
    void Release();
    inline bool Validate() const;
};

bool UGrabber::Validate() const
{
    return PhysicsHandle && Input;
}