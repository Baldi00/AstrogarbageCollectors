
#include "SpaceShipShootingComponent.h"

USpaceShipShootingComponent::USpaceShipShootingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USpaceShipShootingComponent::SetShootingSceneComponents(USceneComponent* Left, USceneComponent* Center, USceneComponent* Right)
{
	LeftLaserRaySceneComponent = Left;
	RightLaserRaySceneComponent = Right;
	CentralDestroyDecomposerSceneComponent = Center;

}

void USpaceShipShootingComponent::ShootLaserRays()
{
	if (GetOwner()->HasAuthority())
	{
		GetWorld()->SpawnActor<AActor>(LaserRayBulletClass,
			LeftLaserRaySceneComponent->GetComponentLocation(), LeftLaserRaySceneComponent->GetComponentRotation());
		GetWorld()->SpawnActor<AActor>(LaserRayBulletClass,
			RightLaserRaySceneComponent->GetComponentLocation(), RightLaserRaySceneComponent->GetComponentRotation());
	}
}

void USpaceShipShootingComponent::ShootDestroyDecomposer()
{
	if (GetOwner()->HasAuthority())
	{
		GetWorld()->SpawnActor<AActor>(DestroyDecomposerBulletClass,
			CentralDestroyDecomposerSceneComponent->GetComponentLocation(),
			CentralDestroyDecomposerSceneComponent->GetComponentRotation());
	}
}

