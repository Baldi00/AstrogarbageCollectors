#include "Bullets/LaserRayBullet.h"
#include "Kismet/KismetMathLibrary.h"
#include "AsteroidInterface.h"
#include "SpaceShipPlayerStateInterface.h"
#include "GameFramework/PlayerState.h"

ALaserRayBullet::ALaserRayBullet()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ALaserRayBullet::OnCollisionHappened()
{
    if (bAlreadyHit)
        return;
    bAlreadyHit = true;

    AActor* HitActor = HitResult.GetActor();
    if (HitActor->ActorHasTag("SpaceShip") || HitActor->ActorHasTag("Checkpoint") || HitActor->ActorHasTag("Satellite"))
    {
        SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),
            GetActorLocation() + UKismetMathLibrary::GetReflectionVector(GetActorForwardVector(), HitResult.Normal)));
    }

    if (HitActor->ActorHasTag("Asteroid"))
        if (IAsteroidInterface* Asteroid = Cast<IAsteroidInterface>(HitActor))
        {
            if (Asteroid->IsAlreadyDestroyed())
                return;

            Asteroid->DestroyAsteroid();

            if (HasAuthority())
            {
                if (APawn* OwnerPawn = Cast<APawn>(Owner))
                {
                    ISpaceShipPlayerStateInterface* PlayerState = Cast<ISpaceShipPlayerStateInterface>(OwnerPawn->GetPlayerState());
                    PlayerState->IncreaseAsteroidsDestroyed();
                    PlayerState->OnRep_AsteroidsDestroyed();
                }
            }

            Destroy();
        }
}