#include "SpaceShipMovementComponent.h"
#include "SpaceShip.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "NiagaraComponent.h"

USpaceShipMovementComponent::USpaceShipMovementComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USpaceShipMovementComponent::BeginPlay()
{
    Super::BeginPlay();

    Owner = Cast<ASpaceShip>(GetOwner());
    ensureMsgf(Owner != nullptr, TEXT("USpaceShipMovementComponent::BeginPlay, Owning actor isn't of type APawn"));

    SpaceShipMeshComponent = GetOwner()->GetComponentByClass<UStaticMeshComponent>();
    ensureMsgf(SpaceShipMeshComponent != nullptr, TEXT("USpaceShipMovementComponent::BeginPlay, Unable to find StaticMesh Component on owning Actor"));

    SpaceShipSpringArmComponent = GetOwner()->GetComponentByClass<USpringArmComponent>();
    ensureMsgf(SpaceShipSpringArmComponent != nullptr, TEXT("USpaceShipMovementComponent::BeginPlay, Unable to find SpringArm Component on owning Actor"));

    SpaceShipCameraComponent = GetOwner()->GetComponentByClass<UCameraComponent>();
    ensureMsgf(SpaceShipCameraComponent != nullptr, TEXT("USpaceShipMovementComponent::BeginPlay, Unable to find Camera Component on owning Actor"));

    TSet<UActorComponent*> Components = GetOwner()->GetComponents();
    int Index = 0;
    for (UActorComponent* Component : Components)
        if (UNiagaraComponent* NiagaraComponent = Cast<UNiagaraComponent>(Component))
            switch (Index)
            {
            case 0: FireRocketComponent1 = NiagaraComponent; Index++; break;
            case 1: FireRocketComponent2 = NiagaraComponent; Index++; break;
            case 2: FireRocketComponent3 = NiagaraComponent; Index++; break;
            default: break;
            }

    DefaultCameraSocketOffset = SpaceShipSpringArmComponent->SocketOffset.Z;
}

void USpaceShipMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    UpdateVelocity(DeltaTime);
    UpdateMovementEffects(DeltaTime);
}

void USpaceShipMovementComponent::Rotate(const FVector2D& LookVector)
{
    Owner->AddActorWorldRotation(FRotator(0, LookVector.X, 0));

    if (Owner->HasAuthority())
        Owner->UpdateReplicatedActorRotation();
}

void USpaceShipMovementComponent::UpdateVelocity(float DeltaTime)
{
    if (CurrentMovementVector != FVector::ZeroVector)
    {
        FVector Movement = FVector::ZeroVector;
        Movement += CurrentMovementVector.X * Owner->GetActorRightVector();
        Movement += CurrentMovementVector.Y * Owner->GetActorForwardVector();
        Movement += CurrentMovementVector.Z * Owner->GetActorUpVector();
        SpaceShipVelocity += DeltaTime * Acceleration * Movement;

        if (SpaceShipVelocity.SquaredLength() > MaxSpeed * MaxSpeed)
            SpaceShipVelocity = SpaceShipVelocity.GetSafeNormal() * MaxSpeed;
    }

    if (bDecreaseVelocity)
        SpaceShipVelocity = FMath::VInterpTo(SpaceShipVelocity, FVector::ZeroVector, DeltaTime, 1);

    Owner->AddActorWorldOffset(SpaceShipVelocity);

    if (Owner->HasAuthority())
        Owner->UpdateReplicatedActorLocation();
}

void USpaceShipMovementComponent::UpdateMovementEffects(float DeltaTime)
{
    float VelocityMagnitude = SpaceShipVelocity.Length();

    UpdateSpaceShipRotation(DeltaTime);
    UpdateCameraSocketOffset(DeltaTime);
    UpdateForwardInputSmoothedTimer(DeltaTime);

    float CurrentFireRocketsLength = FMath::Lerp(0.f, 600.f, ForwardInputSmoothedTimer / ForwardInputSmoothedMaxDuration);

    float CurrentFireRockets1Scale = FMath::Lerp(60.f, 90.f, ForwardInputSmoothedTimer / ForwardInputSmoothedMaxDuration);

    float CurrentFireRockets23Scale = FMath::Lerp(20.f, 50.f, ForwardInputSmoothedTimer / ForwardInputSmoothedMaxDuration);

    FireRocketComponent1->SetFloatParameter("Length", CurrentFireRocketsLength);
    FireRocketComponent2->SetFloatParameter("Length", CurrentFireRocketsLength * 0.75f);
    FireRocketComponent3->SetFloatParameter("Length", CurrentFireRocketsLength * 0.75f);

    FireRocketComponent1->SetFloatParameter("Scale", CurrentFireRockets1Scale);
    FireRocketComponent2->SetFloatParameter("Scale", CurrentFireRockets23Scale);
    FireRocketComponent3->SetFloatParameter("Scale", CurrentFireRockets23Scale);

    // Update Camera Field of View
    SpaceShipCameraComponent->FieldOfView = FMath::Lerp(90.f, 120.f,
        (VelocityMagnitude * ForwardInputSmoothedTimer / ForwardInputSmoothedMaxDuration) / MaxSpeed);
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