#include "SpaceShipShootingComponent.h"
#include "Bullets/LaserRayBullet.h"
#include "Bullets/DestroyDecomposerBullet.h"
#include "SpaceShipPlayerStateInterface.h"
#include "GameFramework/PlayerState.h"

USpaceShipShootingComponent::USpaceShipShootingComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USpaceShipShootingComponent::BeginPlay()
{
    Super::BeginPlay();

    Owner = Cast<APawn>(GetOwner());
    ensureMsgf(Owner != nullptr, TEXT("USpaceShipShootingComponent::BeginPlay, Owning actor isn't of type APawn"));

    Recharge();
}

void USpaceShipShootingComponent::SetShootingSceneComponents(USceneComponent* Left, USceneComponent* Center, USceneComponent* Right)
{
    LeftLaserRaySceneComponent = Left;
    RightLaserRaySceneComponent = Right;
    CentralDestroyDecomposerSceneComponent = Center;
}

void USpaceShipShootingComponent::ShootLaserRays(FRotator BulletsRotation)
{
    if (Owner->HasAuthority())
    {
        if (CurrentLaserRayAmmo < 2)
            return;

        ALaserRayBullet* LaserRayBullet1 = GetWorld()->SpawnActor<ALaserRayBullet>(LaserRayBulletClass,
            LeftLaserRaySceneComponent->GetComponentLocation(), BulletsRotation);
        ALaserRayBullet* LaserRayBullet2 = GetWorld()->SpawnActor<ALaserRayBullet>(LaserRayBulletClass,
            RightLaserRaySceneComponent->GetComponentLocation(), BulletsRotation);

        LaserRayBullet1->AddCollisionIgnoredActor(Owner);
        LaserRayBullet2->AddCollisionIgnoredActor(Owner);
    }
    UpdateAmmoCount(CurrentLaserRayAmmo - 2, CurrentDestroyDecomposerAmmo);
}

void USpaceShipShootingComponent::ShootDestroyDecomposer(FRotator BulletRotation)
{
    if (Owner->HasAuthority())
    {
        if (CurrentDestroyDecomposerAmmo <= 0)
            return;

        ADestroyDecomposerBullet* DestroyDecomposerBullet = GetWorld()->SpawnActor<ADestroyDecomposerBullet>(DestroyDecomposerBulletClass,
            CentralDestroyDecomposerSceneComponent->GetComponentLocation(), BulletRotation);

        DestroyDecomposerBullet->AddCollisionIgnoredActor(Owner);
    }
    UpdateAmmoCount(CurrentLaserRayAmmo, CurrentDestroyDecomposerAmmo - 1);
}

void USpaceShipShootingComponent::Recharge()
{
    UpdateAmmoCount(MaxLaserRayAmmo, MaxDestroyDecomposerAmmo);
}

void USpaceShipShootingComponent::SetPlayerState(APlayerState* InPlayerState)
{
    PlayerState = Cast<ISpaceShipPlayerStateInterface>(InPlayerState);
}

void USpaceShipShootingComponent::UpdateAmmoCount(int32 InCurrentLaserRayAmmo, int32 InCurrentDestroyDecomposerAmmo)
{
    CurrentLaserRayAmmo = InCurrentLaserRayAmmo;
    CurrentDestroyDecomposerAmmo = InCurrentDestroyDecomposerAmmo;

    if (PlayerState)
    {
        PlayerState->SetLaserRayAmmo(CurrentLaserRayAmmo);
        PlayerState->SetDestroyDecomposerAmmo(CurrentDestroyDecomposerAmmo);
        if (Owner->HasAuthority())
        {
            PlayerState->OnRep_LaserRayAmmo();
            PlayerState->OnRep_DestroyDecomposerAmmo();
        }
    }

    OnAmmoUpdated.Broadcast(CurrentLaserRayAmmo, CurrentDestroyDecomposerAmmo);
}