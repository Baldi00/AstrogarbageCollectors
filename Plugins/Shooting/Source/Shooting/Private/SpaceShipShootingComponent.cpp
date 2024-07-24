#include "SpaceShipShootingComponent.h"
#include "Bullets/LaserRayBullet.h"
#include "Bullets/DestroyDecomposerBullet.h"

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

void USpaceShipShootingComponent::ShootLaserRays(FRotator BulletsRotation, AActor* Shooter)
{
	if (GetOwner()->HasAuthority())
	{
		ALaserRayBullet* LaserRayBullet1 = GetWorld()->SpawnActor<ALaserRayBullet>(LaserRayBulletClass,
			LeftLaserRaySceneComponent->GetComponentLocation(), BulletsRotation);
		ALaserRayBullet* LaserRayBullet2 = GetWorld()->SpawnActor<ALaserRayBullet>(LaserRayBulletClass,
			RightLaserRaySceneComponent->GetComponentLocation(), BulletsRotation);

		LaserRayBullet1->AddCollisionIgnoredActor(Shooter);
		LaserRayBullet2->AddCollisionIgnoredActor(Shooter);
	}
}

void USpaceShipShootingComponent::ShootDestroyDecomposer(FRotator BulletRotation, AActor* Shooter)
{
	if (GetOwner()->HasAuthority())
	{
		ADestroyDecomposerBullet* DestroyDecomposerBullet = GetWorld()->SpawnActor<ADestroyDecomposerBullet>(DestroyDecomposerBulletClass,
			CentralDestroyDecomposerSceneComponent->GetComponentLocation(), BulletRotation);

		DestroyDecomposerBullet->AddCollisionIgnoredActor(Shooter);
	}
}

