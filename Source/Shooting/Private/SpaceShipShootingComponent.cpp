#include "SpaceShipShootingComponent.h"
#include "Bullets/LaserRayBullet.h"
#include "Bullets/DestroyDecomposerBullet.h"

USpaceShipShootingComponent::USpaceShipShootingComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USpaceShipShootingComponent::BeginPlay()
{
    Super::BeginPlay();
    Recharge();
}

void USpaceShipShootingComponent::SetShootingSceneComponents(USceneComponent* Left, USceneComponent* Center, USceneComponent* Right)
{
    LeftLaserRaySceneComponent = Left;
    RightLaserRaySceneComponent = Right;
    CentralDestroyDecomposerSceneComponent = Center;
}

void USpaceShipShootingComponent::ShootLaserRays(FRotator BulletsRotation, USpaceShipShootingComponent* Shooter)
{
    if (GetOwner()->HasAuthority())
    {
        if (Shooter->CurrentLaserRayAmmo < 2)
            return;

        ALaserRayBullet* LaserRayBullet1 = GetWorld()->SpawnActor<ALaserRayBullet>(LaserRayBulletClass,
            LeftLaserRaySceneComponent->GetComponentLocation(), BulletsRotation);
        ALaserRayBullet* LaserRayBullet2 = GetWorld()->SpawnActor<ALaserRayBullet>(LaserRayBulletClass,
            RightLaserRaySceneComponent->GetComponentLocation(), BulletsRotation);

        LaserRayBullet1->AddCollisionIgnoredActor(Shooter->GetOwner());
        LaserRayBullet2->AddCollisionIgnoredActor(Shooter->GetOwner());
        Shooter->CurrentLaserRayAmmo -= 2;
        Shooter->OnAmmoUpdated.Broadcast(CurrentLaserRayAmmo, CurrentDestroyDecomposerAmmo);
    }
}

void USpaceShipShootingComponent::ShootDestroyDecomposer(FRotator BulletRotation, USpaceShipShootingComponent* Shooter)
{
    if (GetOwner()->HasAuthority())
    {
        if (Shooter->CurrentDestroyDecomposerAmmo <= 0)
            return;

        ADestroyDecomposerBullet* DestroyDecomposerBullet = GetWorld()->SpawnActor<ADestroyDecomposerBullet>(DestroyDecomposerBulletClass,
            CentralDestroyDecomposerSceneComponent->GetComponentLocation(), BulletRotation);

        DestroyDecomposerBullet->AddCollisionIgnoredActor(Shooter->GetOwner());
        Shooter->CurrentDestroyDecomposerAmmo--;
        Shooter->OnAmmoUpdated.Broadcast(CurrentLaserRayAmmo, CurrentDestroyDecomposerAmmo);
    }
}

void USpaceShipShootingComponent::Recharge()
{
    CurrentLaserRayAmmo = MaxLaserRayAmmo;
    CurrentDestroyDecomposerAmmo = MaxDestroyDecomposerAmmo;
    OnAmmoUpdated.Broadcast(CurrentLaserRayAmmo, CurrentDestroyDecomposerAmmo);
}