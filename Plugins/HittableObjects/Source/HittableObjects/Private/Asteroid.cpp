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