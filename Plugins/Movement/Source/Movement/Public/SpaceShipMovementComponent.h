#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "SpaceShipMovementComponent.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MOVEMENT_API USpaceShipMovementComponent : public UMovementComponent
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float MaxSpeed = 20;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float Acceleration = 20;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float MaxPitchAngle = 4.5f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float MaxRollAngle = 7.5f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float PitchSpeed = 10;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float RollSpeed = 20;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float CameraSocketMaxOffset = 50;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float CameraSocketOffsetSpeed = 200;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float ForwardInputSmoothedMaxDuration = 1;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float ForwardInputSmoothedDecaySpeed = 1;

    FVector Velocity = FVector::ZeroVector;
    FVector CurrentMovementVector = FVector::ZeroVector;

    float TimeToReachMaxSpeedTimer = 0;
    float DefaultCameraSocketOffset = 500;

    float ForwardInputSmoothedTimer = 0;

    APawn* Owner = nullptr;
    UStaticMeshComponent* SpaceShipMeshComponent = nullptr;
    USpringArmComponent* SpaceShipSpringArmComponent = nullptr;
    UCameraComponent* SpaceShipCameraComponent = nullptr;

public:
    USpaceShipMovementComponent();

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void Move(const FVector& MovementVector) { CurrentMovementVector = MovementVector; }
    void Look(const FVector2D& LookVector);

private:
    void UpdateSpaceShipRotation(float DeltaTime);
};
