#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "DestroyDecomposerBullet.generated.h"

UCLASS()
class SHOOTING_API ADestroyDecomposerBullet : public ABullet
{
	GENERATED_BODY()
	
public:	
	ADestroyDecomposerBullet();

protected:
	virtual void OnCollisionHappened() override;
};
