#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RemotePlayerUIWidget.generated.h"

class UProgressBar;
class UTextBlock;
class ASpaceShipPlayerState;

UCLASS()
class UI_API URemotePlayerUIWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(Transient, BlueprintReadOnly, meta = (BindWidget), DisplayName = "Player Name")
	TObjectPtr<UTextBlock> PlayerName = nullptr;

	UPROPERTY(Transient, BlueprintReadOnly, meta = (BindWidget), DisplayName = "Fuel Bar")
	TObjectPtr<UProgressBar> FuelBar = nullptr;

	UPROPERTY(Transient, BlueprintReadOnly, meta = (BindWidget), DisplayName = "Laser Ray Ammo Count")
	TObjectPtr<UTextBlock> LaserRayAmmoCount = nullptr;

	UPROPERTY(Transient, BlueprintReadOnly, meta = (BindWidget), DisplayName = "Destroy Decomposer Ammo Count")
	TObjectPtr<UTextBlock> DestroyDecomposerAmmoCount = nullptr;

	UPROPERTY(Transient, BlueprintReadOnly, meta = (BindWidget), DisplayName = "Destroyed Asteroids Count")
	TObjectPtr<UTextBlock> DestroyedAsteroidsCount = nullptr;

	UPROPERTY(Transient, BlueprintReadOnly, meta = (BindWidget), DisplayName = "Destroyed Satellites Count")
	TObjectPtr<UTextBlock> DestroyedSatellitesCount = nullptr;

private:
	TWeakObjectPtr<ASpaceShipPlayerState> PlayerState;

protected:
	virtual void NativeDestruct() override;

public:
	void SetPlayerState(APlayerState* InPlayerState);
	void SetBindings();
	void ResetBindings();

private:
	UFUNCTION()
	void UpdatePlayerName(FString InPlayerName);
	UFUNCTION()
	void UpdateFuelBar(float InCurrentFuelLevel);
	UFUNCTION()
	void UpdateLaserRayAmmoCount(int32 InCurrentLaserRayAmmoCount);
	UFUNCTION()
	void UpdateDestroyDecomposerAmmoCount(int32 InCurrentDestroyDecomposerAmmoCount);
	UFUNCTION()
	void UpdateDestroyedAsteroidsCount(int32 InCurrentDestroyedAsteroidsCount);
	UFUNCTION()
	void UpdateDestroyedSatellitesCount(int32 InCurrentDestroyedSatellitesCount);
};
