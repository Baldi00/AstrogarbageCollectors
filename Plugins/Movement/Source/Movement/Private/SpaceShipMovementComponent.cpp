#include "SpaceShipMovementComponent.h"

USpaceShipMovementComponent::USpaceShipMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USpaceShipMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector Movement = FVector::ZeroVector;
	Movement += CurrentMovementVector.X * DeltaTime * Speed * GetOwner()->GetActorRightVector();
	Movement += CurrentMovementVector.Y * DeltaTime * Speed * GetOwner()->GetActorForwardVector();
	
	GetOwner()->AddActorWorldOffset(Movement);
}
