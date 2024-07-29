#pragma once

#include "CoreMinimal.h"
#include "HittableObject.h"
#include "AsteroidInterface.h"
#include "Asteroid.generated.h"

UCLASS()
class HITTABLEOBJECTS_API AAsteroid : public AHittableObject, public IAsteroidInterface
{
	GENERATED_BODY()

public:
	AAsteroid();

	UFUNCTION(BlueprintImplementableEvent)
	void StartDestroyAnimation();

	UFUNCTION(BlueprintCallable)
	void OnDestroyAnimationEnded();

	void DestroyAsteroid() override;
};
