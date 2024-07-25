#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpaceShipShootingComponent.generated.h"

class USceneComponent;
class ALaserRayBullet;
class ADestroyDecomposerBullet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAmmoUpdated, int32, InCurrentLaserRayAmmo, int32, InCurrentDestroyDecomposerAmmo);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTING_API USpaceShipShootingComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ALaserRayBullet> LaserRayBulletClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ADestroyDecomposerBullet> DestroyDecomposerBulletClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ammo", meta = (AllowPrivateAccess = "true"))
	int32 MaxLaserRayAmmo = 30;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ammo", meta = (AllowPrivateAccess = "true"))
	int32 MaxDestroyDecomposerAmmo = 8;

	UPROPERTY(BlueprintAssignable)
	FOnAmmoUpdated OnAmmoUpdated;

	int32 CurrentLaserRayAmmo = 0;
	int32 CurrentDestroyDecomposerAmmo = 0;

	USceneComponent* LeftLaserRaySceneComponent = nullptr;
	USceneComponent* RightLaserRaySceneComponent = nullptr;
	USceneComponent* CentralDestroyDecomposerSceneComponent = nullptr;

public:	
	USpaceShipShootingComponent();

protected:
	virtual void BeginPlay() override;

public:
	void SetShootingSceneComponents(USceneComponent* Left, USceneComponent* Center, USceneComponent* Right);
	void ShootLaserRays(FRotator BulletsRotation, USpaceShipShootingComponent* Shooter);
	void ShootDestroyDecomposer(FRotator BulletRotation, USpaceShipShootingComponent* Shooter);

	void Recharge();
};
