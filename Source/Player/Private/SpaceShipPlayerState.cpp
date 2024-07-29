#include "SpaceShipPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "ABLog.h"

void ASpaceShipPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME_CONDITION_NOTIFY(ASpaceShipPlayerState, FuelLevel, COND_None, REPNOTIFY_OnChanged);
    DOREPLIFETIME_CONDITION_NOTIFY(ASpaceShipPlayerState, LaserRayAmmo, COND_None, REPNOTIFY_OnChanged);
    DOREPLIFETIME_CONDITION_NOTIFY(ASpaceShipPlayerState, DestroyDecomposerAmmo, COND_None, REPNOTIFY_OnChanged);
    DOREPLIFETIME_CONDITION_NOTIFY(ASpaceShipPlayerState, AsteroidsDestroyed, COND_None, REPNOTIFY_OnChanged);
    DOREPLIFETIME_CONDITION_NOTIFY(ASpaceShipPlayerState, SatellitesDestroyed, COND_None, REPNOTIFY_OnChanged);
}

void ASpaceShipPlayerState::OnRep_FuelLevel()
{
    LOGF("Fuel level replicated on %s", *GetName());
}

void ASpaceShipPlayerState::OnRep_LaserRayAmmo()
{
    LOGF("Laser ray ammo replicated on %s", *GetName());
}

void ASpaceShipPlayerState::OnRep_DestroyDecomposerAmmo()
{
    LOGF("Destroy decomposer ammo replicated on %s", *GetName());
}

void ASpaceShipPlayerState::OnRep_AsteroidsDestroyed()
{
}

void ASpaceShipPlayerState::OnRep_SatellitesDestroyed()
{
}