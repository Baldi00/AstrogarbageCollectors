#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SpaceShipPlayerStateInterface.h"
#include "SpaceShipPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpaceShipNameUpdated, FString, SpaceShipName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStateFuelLevelUpdated, float, InCurrentFuelLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLaserRayAmmoUpdated, int32, InCurrentLaserRayAmmo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDestroyDecomposerAmmoUpdated, int32, InCurrentDestroyDecomposerAmmo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDestroyedAsteroidsCountUpdated, int32, InCurrentDestroyedAsteroidsCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDestroyedSatellitesCountUpdated, int32, InCurrentDestroyedSatellitesCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerLocationUpdated, FVector, InCurrentPlayerLocation);

UCLASS()
class PLAYER_API ASpaceShipPlayerState : public APlayerState, public ISpaceShipPlayerStateInterface
{
    GENERATED_BODY()

    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = "OnRep_SpaceShipName", meta = (AllowPrivateAccess = "true"))
    FString SpaceShipName = "Player";

    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = "OnRep_FuelLevel", meta = (AllowPrivateAccess = "true"))
    float FuelLevel = 0;

    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = "OnRep_LaserRayAmmo", meta = (AllowPrivateAccess = "true"))
    int32 LaserRayAmmo = 0;
    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = "OnRep_DestroyDecomposerAmmo", meta = (AllowPrivateAccess = "true"))
    int32 DestroyDecomposerAmmo = 0;

    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = "OnRep_AsteroidsDestroyed", meta = (AllowPrivateAccess = "true"))
    int32 AsteroidsDestroyed = 0;
    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = "OnRep_SatellitesDestroyed", meta = (AllowPrivateAccess = "true"))
    int32 SatellitesDestroyed = 0;

    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = "OnRep_PlayerLocation", meta = (AllowPrivateAccess = "true"))
    FVector PlayerLocation;

public:
    virtual void SetSpaceShipName(FString InSpaceShipName) override { SpaceShipName = InSpaceShipName; OnSpaceShipNameUpdated.Broadcast(SpaceShipName); }
    virtual void SetFuelLevel(float InFuelLevel) override { FuelLevel = InFuelLevel; OnPlayerStateFuelLevelUpdated.Broadcast(FuelLevel); }
    virtual void SetLaserRayAmmo(int32 InLaserRayAmmo) override { LaserRayAmmo = InLaserRayAmmo; OnLaserRayAmmoUpdated.Broadcast(LaserRayAmmo); }
    virtual void SetDestroyDecomposerAmmo(int32 InDestroyDecomposerAmmo) override { DestroyDecomposerAmmo = InDestroyDecomposerAmmo; OnDestroyDecomposerAmmoUpdated.Broadcast(DestroyDecomposerAmmo); }
    virtual void IncreaseAsteroidsDestroyed() override { AsteroidsDestroyed++; OnDestroyedAsteroidsCountUpdated.Broadcast(AsteroidsDestroyed); }
    virtual void IncreaseSatellitesDestroyed() override { SatellitesDestroyed++; OnDestroyedSatellitesCountUpdated.Broadcast(SatellitesDestroyed); }
    virtual void SetPlayerLocation(const FVector& InPlayerLocation) override { PlayerLocation = InPlayerLocation; OnPlayerLocationUpdated.Broadcast(PlayerLocation); }

    virtual FString GetSpaceShipName() const override { return SpaceShipName; }
    virtual float GetFuelLevel() const override { return FuelLevel; }
    virtual int32 GetLaserRayAmmo() const override { return LaserRayAmmo; }
    virtual int32 GetDestroyDecomposerAmmo() const override { return DestroyDecomposerAmmo; }
    virtual int32 GetAsteroidsDestroyed() const override { return AsteroidsDestroyed; }
    virtual int32 GetSatellitesDestroyed() const override { return SatellitesDestroyed; }
    virtual const FVector& GetPlayerLocation() const override { return PlayerLocation; }

    UFUNCTION()
    virtual void OnRep_SpaceShipName() override;
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
    UFUNCTION()
    virtual void OnRep_PlayerLocation() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UPROPERTY(BlueprintAssignable)
    FOnSpaceShipNameUpdated OnSpaceShipNameUpdated;
    UPROPERTY(BlueprintAssignable)
    FOnPlayerStateFuelLevelUpdated OnPlayerStateFuelLevelUpdated;
    UPROPERTY(BlueprintAssignable)
    FOnLaserRayAmmoUpdated OnLaserRayAmmoUpdated;
    UPROPERTY(BlueprintAssignable)
    FOnDestroyDecomposerAmmoUpdated OnDestroyDecomposerAmmoUpdated;
    UPROPERTY(BlueprintAssignable)
    FOnDestroyedAsteroidsCountUpdated OnDestroyedAsteroidsCountUpdated;
    UPROPERTY(BlueprintAssignable)
    FOnDestroyedSatellitesCountUpdated OnDestroyedSatellitesCountUpdated;
    UPROPERTY(BlueprintAssignable)
    FOnPlayerLocationUpdated OnPlayerLocationUpdated;
};
