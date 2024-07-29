#include "SpaceShipShootingComponent.h"
#include "Bullets/LaserRayBullet.h"
#include "Bullets/DestroyDecomposerBullet.h"
#include "SpaceShipPlayerStateInterface.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"

USpaceShipShootingComponent::USpaceShipShootingComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    SetIsReplicatedByDefault(true);
}

void USpaceShipShootingComponent::BeginPlay()
{
    Super::BeginPlay();

    Owner = Cast<APawn>(GetOwner());
    ensureMsgf(Owner != nullptr, TEXT("USpaceShipShootingComponent::BeginPlay, Owning actor isn't of type APawn"));

    Recharge();
}

void USpaceShipShootingComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME_CONDITION_NOTIFY(USpaceShipShootingComponent, CurrentLaserRayAmmo, COND_None, REPNOTIFY_OnChanged);
    DOREPLIFETIME_CONDITION_NOTIFY(USpaceShipShootingComponent, CurrentDestroyDecomposerAmmo, COND_None, REPNOTIFY_OnChanged);
}

void USpaceShipShootingComponent::OnRep_CurrentLaserRayAmmo()
{
    OnAmmoUpdated.Broadcast(CurrentLaserRayAmmo, CurrentDestroyDecomposerAmmo);
}

void USpaceShipShootingComponent::OnRep_CurrentDestroyDecomposerAmmo()
{
    OnAmmoUpdated.Broadcast(CurrentLaserRayAmmo, CurrentDestroyDecomposerAmmo);
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
        UpdateAmmoCount(CurrentLaserRayAmmo - 2, CurrentDestroyDecomposerAmmo);
    }
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
        UpdateAmmoCount(CurrentLaserRayAmmo, CurrentDestroyDecomposerAmmo - 1);
    }
}

void USpaceShipShootingComponent::Recharge()
{
    if (Owner->HasAuthority())
        UpdateAmmoCount(MaxLaserRayAmmo, MaxDestroyDecomposerAmmo);
}

void USpaceShipShootingComponent::SetPlayerState(APlayerState* InPlayerState)
{
    PlayerState = Cast<ISpaceShipPlayerStateInterface>(InPlayerState);
}

void USpaceShipShootingComponent::UpdateAmmoCount(int32 InCurrentLaserRayAmmo, int32 InCurrentDestroyDecomposerAmmo)
{
    if (Owner->HasAuthority())
    {
        CurrentLaserRayAmmo = InCurrentLaserRayAmmo;
        CurrentDestroyDecomposerAmmo = InCurrentDestroyDecomposerAmmo;

        OnRep_CurrentLaserRayAmmo();
        OnRep_CurrentDestroyDecomposerAmmo();

        if (PlayerState)
        {
            PlayerState->SetLaserRayAmmo(CurrentLaserRayAmmo);
            PlayerState->SetDestroyDecomposerAmmo(CurrentDestroyDecomposerAmmo);
            PlayerState->OnRep_LaserRayAmmo();
            PlayerState->OnRep_DestroyDecomposerAmmo();
        }
    }
}