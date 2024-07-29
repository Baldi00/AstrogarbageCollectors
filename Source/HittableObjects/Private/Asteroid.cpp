#include "Asteroid.h"

AAsteroid::AAsteroid()
{
    Tags.AddUnique("Asteroid");
}

void AAsteroid::OnDestroyAnimationEnded()
{
    if (HasAuthority())
        Destroy();
}

void AAsteroid::DestroyAsteroid()
{
    if (bAlreadyHit)
        return;
    bAlreadyHit = true;
    StartDestroyAnimation();
}

bool AAsteroid::IsAlreadyDestroyed()
{
    return bAlreadyHit;
}
