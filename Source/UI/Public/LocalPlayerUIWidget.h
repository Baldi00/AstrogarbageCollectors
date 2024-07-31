#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LocalPlayerUIWidget.generated.h"

class UProgressBar;
class UTextBlock;
class USpaceShipMovementComponent;
class USpaceShipShootingComponent;
class ASpaceShipPlayerState;
class AAGCGameState;

UCLASS()
class UI_API ULocalPlayerUIWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(Transient, BlueprintReadOnly, meta = (BindWidget), DisplayName = "Fuel Bar")
	TObjectPtr<UProgressBar> FuelBar = nullptr;

	UPROPERTY(Transient, BlueprintReadOnly, meta = (BindWidget), DisplayName = "Timer")
	TObjectPtr<UTextBlock> Timer = nullptr;

	UPROPERTY(Transient, BlueprintReadOnly, meta = (BindWidget), DisplayName = "Laser Ray Ammo Count")
	TObjectPtr<UTextBlock> LaserRayAmmoCount = nullptr;

	UPROPERTY(Transient, BlueprintReadOnly, meta = (BindWidget), DisplayName = "Destroy Decomposer Ammo Count")
	TObjectPtr<UTextBlock> DestroyDecomposerAmmoCount = nullptr;

	UPROPERTY(Transient, BlueprintReadOnly, meta = (BindWidget), DisplayName = "Destroyed Asteroids Count")
	TObjectPtr<UTextBlock> DestroyedAsteroidsCount = nullptr;

	UPROPERTY(Transient, BlueprintReadOnly, meta = (BindWidget), DisplayName = "Destroyed Satellites Count")
	TObjectPtr<UTextBlock> DestroyedSatellitesCount = nullptr;

private:
	TWeakObjectPtr<USpaceShipMovementComponent> MovementComponent;
	TWeakObjectPtr<USpaceShipShootingComponent> ShootingComponent;
	TWeakObjectPtr<ASpaceShipPlayerState> PlayerState;
	TWeakObjectPtr<AAGCGameState> GameState;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetBindings();
	void ResetBindings();

	UFUNCTION()
	void SetPlayerStateBinding(APlayerState* InPlayerState);

private:
	UFUNCTION()
	void UpdateFuelBar(float InCurrentFuelLevel);
	void UpdateTimer(const FString& InCurrentTimerString);
	UFUNCTION()
	void UpdateAmmoCount(int32 InCurrentLaserRayAmmoCount, int32 InCurrentDestroyDecomposerAmmoCount);
	UFUNCTION()
	void UpdateDestroyedAsteroidsCount(int32 InCurrentDestroyedAsteroidsCount);
	UFUNCTION()
	void UpdateDestroyedSatellitesCount(int32 InCurrentDestroyedSatellitesCount);
};
