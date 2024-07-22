#include "SpaceShipMovementComponent.h"

USpaceShipMovementComponent::USpaceShipMovementComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USpaceShipMovementComponent::BeginPlay()
{
    Super::BeginPlay();

    SpaceShipMeshComponent = GetOwner()->GetComponentByClass<UStaticMeshComponent>();
    ensureMsgf(SpaceShipMeshComponent != nullptr, TEXT("USpaceShipMovementComponent::BeginPlay, Unable to find Static Mesh Component on owning Actor"));
}

void USpaceShipMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (CurrentMovementVector != FVector2D::ZeroVector)
    {
        FVector Movement = FVector::ZeroVector;
        Movement += CurrentMovementVector.X * GetOwner()->GetActorRightVector();
        Movement += CurrentMovementVector.Y * GetOwner()->GetActorForwardVector();
        Velocity += DeltaTime * Acceleration * Movement;

        if (Velocity.SquaredLength() > MaxSpeed * MaxSpeed)
            Velocity = Velocity.GetSafeNormal() * MaxSpeed;
    }

    GetOwner()->AddActorWorldOffset(Velocity);

    UpdateSpaceShipRotation(DeltaTime);
}

void USpaceShipMovementComponent::UpdateSpaceShipRotation(float DeltaTime)
{
    FRotator NextRotation = SpaceShipMeshComponent->GetRelativeRotation();

    if (CurrentMovementVector.X > 0)
        NextRotation.Roll = FMath::Min(MaxRollAngle, NextRotation.Roll + RollSpeed * DeltaTime);
    else if (CurrentMovementVector.X < 0)
        NextRotation.Roll = FMath::Max(-MaxRollAngle, NextRotation.Roll - RollSpeed * DeltaTime);
    else
    {
        if (NextRotation.Roll > 0)
            NextRotation.Roll = FMath::Max(0, NextRotation.Roll - RollSpeed * DeltaTime);
        else if (NextRotation.Roll < 0)
            NextRotation.Roll = FMath::Min(0, NextRotation.Roll + RollSpeed * DeltaTime);
    }
    
    if (CurrentMovementVector.Y > 0)
        NextRotation.Pitch = FMath::Max(-MaxPitchAngle, NextRotation.Pitch - PitchSpeed * DeltaTime);
    else if (CurrentMovementVector.Y < 0)
        NextRotation.Pitch = FMath::Min(MaxPitchAngle, NextRotation.Pitch + PitchSpeed * DeltaTime);
    else if (NextRotation.Pitch > 0)
        NextRotation.Pitch = FMath::Max(0, NextRotation.Pitch - PitchSpeed * DeltaTime);
    else if (NextRotation.Pitch < 0)
        NextRotation.Pitch = FMath::Min(0, NextRotation.Pitch + PitchSpeed * DeltaTime);

    SpaceShipMeshComponent->SetRelativeRotation(NextRotation);
}
