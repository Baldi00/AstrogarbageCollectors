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
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLaserRaysShooted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDestroyDecomposerShooted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTryingToShootEmptyAmmo);

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, ReplicatedUsing = "OnRep_CurrentLaserRayAmmo", meta = (AllowPrivateAccess = "true"))
	int32 CurrentLaserRayAmmo = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, ReplicatedUsing = "OnRep_CurrentDestroyDecomposerAmmo", meta = (AllowPrivateAccess = "true"))
	int32 CurrentDestroyDecomposerAmmo = 0;

	APawn* Owner = nullptr;
	ISpaceShipPlayerStateInterface* PlayerState = nullptr;
	USceneComponent* LeftLaserRaySceneComponent = nullptr;
	USceneComponent* RightLaserRaySceneComponent = nullptr;
	USceneComponent* CentralDestroyDecomposerSceneComponent = nullptr;

public:	
	USpaceShipShootingComponent();

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_CurrentLaserRayAmmo();
	UFUNCTION()
	void OnRep_CurrentDestroyDecomposerAmmo();

public:
	void OnPossess();
	void SetShootingSceneComponents(USceneComponent* Left, USceneComponent* Center, USceneComponent* Right);
	void ShootLaserRays(FRotator BulletsRotation);
	void ShootDestroyDecomposer(FRotator BulletRotation);

	virtual void Recharge() override;
	void SetPlayerState(APlayerState* InPlayerState);

private:
	void UpdateAmmoCount(int32 InCurrentLaserRayAmmo, int32 InCurrentDestroyDecomposerAmmo);

public:
	UPROPERTY(BlueprintAssignable)
	FOnAmmoUpdated OnAmmoUpdated;
	UPROPERTY(BlueprintAssignable)
	FOnLaserRaysShooted OnLaserRaysShooted;
	UPROPERTY(BlueprintAssignable)
	FOnDestroyDecomposerShooted OnDestroyDecomposerShooted;
	UPROPERTY(BlueprintAssignable)
	FOnTryingToShootEmptyAmmo OnTryingToShootEmptyAmmo;

	int32 GetLaserRayAmmoCount() { return CurrentLaserRayAmmo; }
	int32 GetDestroyDecomposerAmmoCount() { return CurrentDestroyDecomposerAmmo; }
};
