#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SpaceShipPlayerStateInterface.generated.h"

UINTERFACE(MinimalAPI)
class USpaceShipPlayerStateInterface : public UInterface
{
    GENERATED_BODY()
};

class COMMON_API ISpaceShipPlayerStateInterface
{
    GENERATED_BODY()

public:
    virtual void SetSpaceShipName(FString InSpaceShipName) = 0;
    virtual void SetFuelLevel(float InFuelLevel) = 0;
    virtual void SetLaserRayAmmo(int32 InLaserRayAmmo) = 0;
    virtual void SetDestroyDecomposerAmmo(int32 InDestroyDecomposerAmmo) = 0;
    virtual void IncreaseAsteroidsDestroyed() = 0;
    virtual void IncreaseSatellitesDestroyed() = 0;
    virtual void SetAsteroidsDestroyed(int32 InAsteroidsDestroyed) = 0;
    virtual void SetSatellitesDestroyed(int32 InSatellitesDestroyed) = 0;

    virtual FString GetSpaceShipName() const = 0;
    virtual float GetFuelLevel() const = 0;
    virtual int32 GetLaserRayAmmo() const = 0;
    virtual int32 GetDestroyDecomposerAmmo() const = 0;
    virtual int32 GetAsteroidsDestroyed() const = 0;
    virtual int32 GetSatellitesDestroyed() const = 0;

    UFUNCTION()
    virtual void OnRep_SpaceShipName() = 0;
    UFUNCTION()
    virtual void OnRep_FuelLevel() = 0;
    UFUNCTION()
    virtual void OnRep_LaserRayAmmo() = 0;
    UFUNCTION()
    virtual void OnRep_DestroyDecomposerAmmo() = 0;
    UFUNCTION()
    virtual void OnRep_AsteroidsDestroyed() = 0;
    UFUNCTION()
    virtual void OnRep_SatellitesDestroyed() = 0;
};
