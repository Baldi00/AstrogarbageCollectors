#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SpaceShipPlayerStateInterface.h"
#include "SpaceShipPlayerState.generated.h"

UCLASS()
class PLAYER_API ASpaceShipPlayerState : public APlayerState, public ISpaceShipPlayerStateInterface
{
    GENERATED_BODY()

    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = "OnRep_FuelLevel", meta = (AllowPrivateAccess = "true"))
    float FuelLevel = 100;

    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = "OnRep_LaserRayAmmo", meta = (AllowPrivateAccess = "true"))
    int32 LaserRayAmmo = 30;
    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = "OnRep_DestroyDecomposerAmmo", meta = (AllowPrivateAccess = "true"))
    int32 DestroyDecomposerAmmo = 8;

    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = "OnRep_AsteroidsDestroyed", meta = (AllowPrivateAccess = "true"))
    int32 AsteroidsDestroyed = 0;
    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = "OnRep_SatellitesDestroyed", meta = (AllowPrivateAccess = "true"))
    int32 SatellitesDestroyed = 0;

public:
    virtual void SetFuelLevel(float InFuelLevel) override { FuelLevel = InFuelLevel; }
    virtual void SetLaserRayAmmo(int32 InLaserRayAmmo) override { LaserRayAmmo = InLaserRayAmmo; }
    virtual void SetDestroyDecomposerAmmo(int32 InDestroyDecomposerAmmo) override { DestroyDecomposerAmmo = InDestroyDecomposerAmmo; }
    virtual void IncreaseAsteroidsDestroyed() override { AsteroidsDestroyed++; }
    virtual void IncreaseSatellitesDestroyed() override { SatellitesDestroyed++; }

    virtual float GetFuelLevel() const override { return FuelLevel; }
    virtual int32 GetLaserRayAmmo() const override { return LaserRayAmmo; }
    virtual int32 GetDestroyDecomposerAmmo() const override { return DestroyDecomposerAmmo; }
    virtual int32 GetAsteroidsDestroyed() const override { return AsteroidsDestroyed; }
    virtual int32 GetSatellitesDestroyed() const override { return SatellitesDestroyed; }

    UFUNCTION()
    virtual void OnRep_FuelLevel() override;
    UFUNCTION()
    virtual void OnRep_LaserRayAmmo() override;
    UFUNCTION()
    virtual void OnRep_DestroyDecomposerAmmo() override;
    UFUNCTION()
    virtual void OnRep_AsteroidsDestroyed() override;
    UFUNCTION()
    virtual void OnRep_SatellitesDestroyed() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
