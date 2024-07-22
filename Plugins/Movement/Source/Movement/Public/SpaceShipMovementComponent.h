#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "SpaceShipMovementComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MOVEMENT_API USpaceShipMovementComponent : public UMovementComponent
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float MaxSpeed = 500;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float Acceleration = 1;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float MaxPitchAngle = 15;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float MaxRollAngle = 15;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float PitchSpeed = 50;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float RollSpeed = 50;

    FVector Velocity = FVector::ZeroVector;
    FVector2D CurrentMovementVector = FVector2D::ZeroVector;

    float TimeToReachMaxSpeedTimer = 0;

    UStaticMeshComponent* SpaceShipMeshComponent;

public:
    USpaceShipMovementComponent();

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void Move(const FVector2D& MovementVector) { CurrentMovementVector = MovementVector; }

private:
    void UpdateSpaceShipRotation(float DeltaTime);
};
