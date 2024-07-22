#include "SpaceShipMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

USpaceShipMovementComponent::USpaceShipMovementComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USpaceShipMovementComponent::BeginPlay()
{
    Super::BeginPlay();

    Owner = Cast<APawn>(GetOwner());
    ensureMsgf(Owner != nullptr, TEXT("USpaceShipMovementComponent::BeginPlay, Owning actor isn't of type APawn"));

    SpaceShipMeshComponent = GetOwner()->GetComponentByClass<UStaticMeshComponent>();
    ensureMsgf(SpaceShipMeshComponent != nullptr, TEXT("USpaceShipMovementComponent::BeginPlay, Unable to find StaticMesh Component on owning Actor"));

    SpaceShipSpringArmComponent = GetOwner()->GetComponentByClass<USpringArmComponent>();
    ensureMsgf(SpaceShipSpringArmComponent != nullptr, TEXT("USpaceShipMovementComponent::BeginPlay, Unable to find SpringArm Component on owning Actor"));

    SpaceShipCameraComponent = GetOwner()->GetComponentByClass<UCameraComponent>();
    ensureMsgf(SpaceShipCameraComponent != nullptr, TEXT("USpaceShipMovementComponent::BeginPlay, Unable to find Camera Component on owning Actor"));

    DefaultCameraSocketOffset = SpaceShipSpringArmComponent->SocketOffset.Z;
}

void USpaceShipMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    UpdateVelocity(DeltaTime);
    UpdateMovementEffects(DeltaTime);
}

void USpaceShipMovementComponent::Look(const FVector2D& LookVector)
{
    if (Owner->Controller != nullptr)
    {
        Owner->AddControllerYawInput(LookVector.X);
        Owner->AddControllerPitchInput(LookVector.Y);
    }
}

void USpaceShipMovementComponent::UpdateVelocity(float DeltaTime)
{
    if (CurrentMovementVector != FVector::ZeroVector)
    {
        FVector Movement = FVector::ZeroVector;
        Movement += CurrentMovementVector.X * Owner->GetActorRightVector();
        Movement += CurrentMovementVector.Y * Owner->GetActorForwardVector();
        Movement += CurrentMovementVector.Z * Owner->GetActorUpVector();
        Velocity += DeltaTime * Acceleration * Movement;

        if (Velocity.SquaredLength() > MaxSpeed * MaxSpeed)
            Velocity = Velocity.GetSafeNormal() * MaxSpeed;
    }

    Owner->AddActorWorldOffset(Velocity);
}

void USpaceShipMovementComponent::UpdateMovementEffects(float DeltaTime)
{
    UpdateSpaceShipRotation(DeltaTime);
    UpdateCameraSocketOffset(DeltaTime);
    UpdateForwardInputSmoothedTimer(DeltaTime);

    // Update Camera Field of View
    SpaceShipCameraComponent->FieldOfView = FMath::Lerp(90.f, 120.f,
        (Velocity.Length() * ForwardInputSmoothedTimer / ForwardInputSmoothedMaxDuration) / MaxSpeed);
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

void USpaceShipMovementComponent::UpdateCameraSocketOffset(float DeltaTime)
{
    FVector SocketOffset = SpaceShipSpringArmComponent->SocketOffset;

    if (CurrentMovementVector.Z != 0)
        SocketOffset.Z = FMath::Clamp(SocketOffset.Z - CurrentMovementVector.Z * CameraSocketOffsetSpeed * DeltaTime,
            DefaultCameraSocketOffset - CameraSocketMaxOffset, DefaultCameraSocketOffset + CameraSocketMaxOffset);
    else if (SocketOffset.Z > DefaultCameraSocketOffset)
        SocketOffset.Z = FMath::Max(DefaultCameraSocketOffset, SocketOffset.Z - CameraSocketOffsetSpeed * DeltaTime);
    else if (SocketOffset.Z < DefaultCameraSocketOffset)
        SocketOffset.Z = FMath::Min(DefaultCameraSocketOffset, SocketOffset.Z + CameraSocketOffsetSpeed * DeltaTime);

    SpaceShipSpringArmComponent->SocketOffset = SocketOffset;
}

void USpaceShipMovementComponent::UpdateForwardInputSmoothedTimer(float DeltaTime)
{
    if (CurrentMovementVector.Y > 0)
        ForwardInputSmoothedTimer = FMath::Min(ForwardInputSmoothedMaxDuration, ForwardInputSmoothedTimer + DeltaTime);
    else
        ForwardInputSmoothedTimer = FMath::Max(0, ForwardInputSmoothedTimer - DeltaTime * ForwardInputSmoothedDecaySpeed);
}