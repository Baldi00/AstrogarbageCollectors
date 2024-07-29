#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Rechargeable.h"
#include "SpaceShipShootingComponent.generated.h"

class USceneComponent;
class ALaserRayBullet;
class ADestroyDecomposerBullet;
class ISpaceShipPlayerStateInterface;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAmmoUpdated, int32, InCurrentLaserRayAmmo, int32, InCurrentDestroyDecomposerAmmo);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTING_API USpaceShipShootingComponent : public UActorComponent, public IRechargeable
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

	APawn* Owner = nullptr;
	ISpaceShipPlayerStateInterface* PlayerState = nullptr;
	USceneComponent* LeftLaserRaySceneComponent = nullptr;
	USceneComponent* RightLaserRaySceneComponent = nullptr;
	USceneComponent* CentralDestroyDecomposerSceneComponent = nullptr;

public:	
	USpaceShipShootingComponent();

protected:
	virtual void BeginPlay() override;

public:
	void SetShootingSceneComponents(USceneComponent* Left, USceneComponent* Center, USceneComponent* Right);
	void ShootLaserRays(FRotator BulletsRotation);
	void ShootDestroyDecomposer(FRotator BulletRotation);

	virtual void Recharge() override;
	void SetPlayerState(APlayerState* InPlayerState);

private:
	void UpdateAmmoCount(int32 InCurrentLaserRayAmmo, int32 InCurrentDestroyDecomposerAmmo);
};
