#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LocalPlayerUIWidget.generated.h"

class UProgressBar;
class UTextBlock;

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
};
