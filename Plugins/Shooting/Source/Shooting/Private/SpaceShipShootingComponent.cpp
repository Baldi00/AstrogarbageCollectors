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

void USpaceShipShootingComponent::ShootLaserRays(FRotator BulletsRotation)
{
	if (GetOwner()->HasAuthority())
	{
		GetWorld()->SpawnActor<AActor>(LaserRayBulletClass,
			LeftLaserRaySceneComponent->GetComponentLocation(), BulletsRotation);
		GetWorld()->SpawnActor<AActor>(LaserRayBulletClass,
			RightLaserRaySceneComponent->GetComponentLocation(), BulletsRotation);
	}
}

void USpaceShipShootingComponent::ShootDestroyDecomposer(FRotator BulletRotation)
{
	if (GetOwner()->HasAuthority())
	{
		GetWorld()->SpawnActor<AActor>(DestroyDecomposerBulletClass,
			CentralDestroyDecomposerSceneComponent->GetComponentLocation(), BulletRotation);
	}
}

