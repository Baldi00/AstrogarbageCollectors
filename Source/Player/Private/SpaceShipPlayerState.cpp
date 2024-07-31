#include "SpaceShipPlayerState.h"
#include "Net/UnrealNetwork.h"

void ASpaceShipPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME_CONDITION_NOTIFY(ASpaceShipPlayerState, FuelLevel, COND_None, REPNOTIFY_OnChanged);
    DOREPLIFETIME_CONDITION_NOTIFY(ASpaceShipPlayerState, LaserRayAmmo, COND_None, REPNOTIFY_OnChanged);
    DOREPLIFETIME_CONDITION_NOTIFY(ASpaceShipPlayerState, DestroyDecomposerAmmo, COND_None, REPNOTIFY_OnChanged);
    DOREPLIFETIME_CONDITION_NOTIFY(ASpaceShipPlayerState, AsteroidsDestroyed, COND_None, REPNOTIFY_OnChanged);
    DOREPLIFETIME_CONDITION_NOTIFY(ASpaceShipPlayerState, SatellitesDestroyed, COND_None, REPNOTIFY_OnChanged);
    DOREPLIFETIME_CONDITION_NOTIFY(ASpaceShipPlayerState, PlayerLocation, COND_None, REPNOTIFY_OnChanged);
}

void ASpaceShipPlayerState::OnRep_FuelLevel()
{
    OnPlayerStateFuelLevelUpdated.Broadcast(FuelLevel);
}

void ASpaceShipPlayerState::OnRep_LaserRayAmmo()
{
    OnLaserRayAmmoUpdated.Broadcast(LaserRayAmmo);
}

void ASpaceShipPlayerState::OnRep_DestroyDecomposerAmmo()
{
    OnDestroyDecomposerAmmoUpdated.Broadcast(DestroyDecomposerAmmo);
}

void ASpaceShipPlayerState::OnRep_AsteroidsDestroyed()
{
    OnDestroyedAsteroidsCountUpdated.Broadcast(AsteroidsDestroyed);
}

void ASpaceShipPlayerState::OnRep_SatellitesDestroyed()
{
    OnDestroyedSatellitesCountUpdated.Broadcast(SatellitesDestroyed);
}

void ASpaceShipPlayerState::OnRep_PlayerLocation()
{
    OnPlayerLocationUpdated.Broadcast(PlayerLocation);
}