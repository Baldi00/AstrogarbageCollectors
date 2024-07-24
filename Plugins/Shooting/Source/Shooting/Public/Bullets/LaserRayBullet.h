#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "LaserRayBullet.generated.h"

UCLASS()
class SHOOTING_API ALaserRayBullet : public ABullet
{
	GENERATED_BODY()
	
public:	
	ALaserRayBullet();

protected:
	virtual void OnCollisionHappened() override;
};
