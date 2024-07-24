#pragma once

#include "CoreMinimal.h"
#include "HittableObject.h"
#include "Asteroid.generated.h"

UCLASS()
class HITTABLEOBJECTS_API AAsteroid : public AHittableObject
{
	GENERATED_BODY()

public:
	AAsteroid();
};
