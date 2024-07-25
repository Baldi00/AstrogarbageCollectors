#include "Bullets/LaserRayBullet.h"
#include "Kismet/KismetMathLibrary.h"
#include "Asteroid.h"

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
        if (AAsteroid* Asteroid = Cast<AAsteroid>(HitActor))
            Asteroid->StartDestroyAnimation();
}