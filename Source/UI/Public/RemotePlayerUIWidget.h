#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RemotePlayerUIWidget.generated.h"

class UProgressBar;
class UTextBlock;

UCLASS()
class UI_API URemotePlayerUIWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(Transient, BlueprintReadOnly, meta = (BindWidget), DisplayName = "Player Name")
	TObjectPtr<UTextBlock> PlayerName = nullptr;

	UPROPERTY(Transient, BlueprintReadOnly, meta = (BindWidget), DisplayName = "Fuel Bar")
	TObjectPtr<UProgressBar> FuelBar = nullptr;

	UPROPERTY(Transient, BlueprintReadOnly, meta = (BindWidget), DisplayName = "Destroyed Asteroids Count")
	TObjectPtr<UTextBlock> DestroyedAsteroidsCount = nullptr;

	UPROPERTY(Transient, BlueprintReadOnly, meta = (BindWidget), DisplayName = "Destroyed Satellites Count")
	TObjectPtr<UTextBlock> DestroyedSatellitesCount = nullptr;
};
