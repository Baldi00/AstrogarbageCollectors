#include "Bullets/DestroyDecomposerBullet.h"
#include "Bullets/BlackHole.h"

ADestroyDecomposerBullet::ADestroyDecomposerBullet()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ADestroyDecomposerBullet::OnCollisionHappened()
{
    if (HitResult.GetActor()->ActorHasTag("SpaceShip") || HitResult.GetActor()->ActorHasTag("Checkpoint"))
        return;

    if (HasAuthority() && BlackHoleClass)
    {
        ABlackHole* BlackHole = GetWorld()->SpawnActor<ABlackHole>(BlackHoleClass, HitResult.Location, FRotator::ZeroRotator);
        if (BlackHole)
            BlackHole->SetHitActor(HitResult.GetActor());
        Destroy();
    }
}