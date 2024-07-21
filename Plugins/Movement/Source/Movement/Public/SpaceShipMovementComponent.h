#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "SpaceShipMovementComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MOVEMENT_API USpaceShipMovementComponent : public UMovementComponent
{
    GENERATED_BODY()

    FVector2D CurrentMovementVector = FVector2D::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float Speed = 500;

public:
    USpaceShipMovementComponent();

    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void Move(const FVector2D& MovementVector) { CurrentMovementVector = MovementVector; }
};
