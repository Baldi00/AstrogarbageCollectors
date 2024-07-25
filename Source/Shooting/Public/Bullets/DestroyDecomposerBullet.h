#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "DestroyDecomposerBullet.generated.h"

class ABlackHole;

UCLASS()
class SHOOTING_API ADestroyDecomposerBullet : public ABullet
{
	GENERATED_BODY()
	
	UPROPERTY(Category = Bullet, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABlackHole> BlackHoleClass;

public:	
	ADestroyDecomposerBullet();

protected:
	virtual void OnCollisionHappened() override;
};
