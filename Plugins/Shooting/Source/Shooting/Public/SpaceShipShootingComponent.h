#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpaceShipShootingComponent.generated.h"

class USceneComponent;
class ALaserRayBullet;
class ADestroyDecomposerBullet;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTING_API USpaceShipShootingComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ALaserRayBullet> LaserRayBulletClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ADestroyDecomposerBullet> DestroyDecomposerBulletClass;

	USceneComponent* LeftLaserRaySceneComponent = nullptr;
	USceneComponent* RightLaserRaySceneComponent = nullptr;
	USceneComponent* CentralDestroyDecomposerSceneComponent = nullptr;

public:	
	USpaceShipShootingComponent();

	void SetShootingSceneComponents(USceneComponent* Left, USceneComponent* Center, USceneComponent* Right);
	void ShootLaserRays(FRotator BulletsRotation, AActor* Shooter);
	void ShootDestroyDecomposer(FRotator BulletRotation, AActor* Shooter);
};
