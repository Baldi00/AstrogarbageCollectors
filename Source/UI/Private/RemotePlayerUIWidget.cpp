#include "RemotePlayerUIWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "SpaceShipPlayerState.h"

void URemotePlayerUIWidget::NativeDestruct()
{
    ResetBindings();
    PlayerState.Reset();
    Super::NativeDestruct();
}

void URemotePlayerUIWidget::SetPlayerState(APlayerState* InPlayerState)
{
    PlayerState = MakeWeakObjectPtr(Cast<ASpaceShipPlayerState>(InPlayerState));

    UpdatePlayerName(PlayerState->GetSpaceShipName());
    UpdateFuelBar(PlayerState->GetFuelLevel());
    UpdateLaserRayAmmoCount(PlayerState->GetLaserRayAmmo());
    UpdateDestroyDecomposerAmmoCount(PlayerState->GetDestroyDecomposerAmmo());
    UpdateDestroyedAsteroidsCount(PlayerState->GetAsteroidsDestroyed());
    UpdateDestroyedSatellitesCount(PlayerState->GetSatellitesDestroyed());
    SetBindings();
}

void URemotePlayerUIWidget::SetBindings()
{
    ResetBindings();

    PlayerState->OnSpaceShipNameUpdated.AddUniqueDynamic(this, &URemotePlayerUIWidget::UpdatePlayerName);
    PlayerState->OnPlayerStateFuelLevelUpdated.AddUniqueDynamic(this, &URemotePlayerUIWidget::UpdateFuelBar);
    PlayerState->OnLaserRayAmmoUpdated.AddUniqueDynamic(this, &URemotePlayerUIWidget::UpdateLaserRayAmmoCount);
    PlayerState->OnDestroyDecomposerAmmoUpdated.AddUniqueDynamic(this, &URemotePlayerUIWidget::UpdateDestroyDecomposerAmmoCount);
    PlayerState->OnDestroyedAsteroidsCountUpdated.AddUniqueDynamic(this, &URemotePlayerUIWidget::UpdateDestroyedAsteroidsCount);
    PlayerState->OnDestroyedSatellitesCountUpdated.AddUniqueDynamic(this, &URemotePlayerUIWidget::UpdateDestroyedSatellitesCount);
}

void URemotePlayerUIWidget::ResetBindings()
{
    if (PlayerState.IsValid())
    {
        PlayerState->OnSpaceShipNameUpdated.RemoveDynamic(this, &URemotePlayerUIWidget::UpdatePlayerName);
        PlayerState->OnPlayerStateFuelLevelUpdated.RemoveDynamic(this, &URemotePlayerUIWidget::UpdateFuelBar);
        PlayerState->OnLaserRayAmmoUpdated.RemoveDynamic(this, &URemotePlayerUIWidget::UpdateLaserRayAmmoCount);
        PlayerState->OnDestroyDecomposerAmmoUpdated.RemoveDynamic(this, &URemotePlayerUIWidget::UpdateDestroyDecomposerAmmoCount);
        PlayerState->OnDestroyedAsteroidsCountUpdated.RemoveDynamic(this, &URemotePlayerUIWidget::UpdateDestroyedAsteroidsCount);
        PlayerState->OnDestroyedSatellitesCountUpdated.RemoveDynamic(this, &URemotePlayerUIWidget::UpdateDestroyedSatellitesCount);
    }
}

void URemotePlayerUIWidget::UpdatePlayerName(FString InPlayerName)
{
    PlayerName->SetText(FText::FromString(InPlayerName));
}

void URemotePlayerUIWidget::UpdateFuelBar(float InCurrentFuelLevel)
{
    FuelBar->SetPercent(InCurrentFuelLevel / 100);
}

void URemotePlayerUIWidget::UpdateLaserRayAmmoCount(int32 InCurrentLaserRayAmmoCount)
{
    LaserRayAmmoCount->SetText(FText::FromString(FString::Printf(TEXT("%02d"), InCurrentLaserRayAmmoCount)));
}

void URemotePlayerUIWidget::UpdateDestroyDecomposerAmmoCount(int32 InCurrentDestroyDecomposerAmmoCount)
{
    DestroyDecomposerAmmoCount->SetText(FText::FromString(FString::Printf(TEXT("%02d"), InCurrentDestroyDecomposerAmmoCount)));
}

void URemotePlayerUIWidget::UpdateDestroyedAsteroidsCount(int32 InCurrentDestroyedAsteroidsCount)
{
    DestroyedAsteroidsCount->SetText(FText::FromString(FString::Printf(TEXT("%02d"), InCurrentDestroyedAsteroidsCount)));
}

void URemotePlayerUIWidget::UpdateDestroyedSatellitesCount(int32 InCurrentDestroyedSatellitesCount)
{
    DestroyedSatellitesCount->SetText(FText::FromString(FString::Printf(TEXT("%02d"), InCurrentDestroyedSatellitesCount)));
}