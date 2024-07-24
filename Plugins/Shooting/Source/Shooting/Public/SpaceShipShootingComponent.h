#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SceneComponent.h"
#include "Bullets/Bullet.h"
#include "SpaceShipShootingComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTING_API USpaceShipShootingComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABullet> LaserRayBulletClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABullet> DestroyDecomposerBulletClass;

	USceneComponent* LeftLaserRaySceneComponent = nullptr;
	USceneComponent* RightLaserRaySceneComponent = nullptr;
	USceneComponent* CentralDestroyDecomposerSceneComponent = nullptr;

public:	
	USpaceShipShootingComponent();

	void SetShootingSceneComponents(USceneComponent* Left, USceneComponent* Center, USceneComponent* Right);
	void ShootLaserRays(FRotator BulletsRotation);
	void ShootDestroyDecomposer(FRotator BulletRotation);
};
