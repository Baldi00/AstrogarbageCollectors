#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndGameUIWidget.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class UI_API UEndGameUIWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(Transient, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> YourAsteroidsDestroyed = nullptr;
	UPROPERTY(Transient, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TotalAsteroidsDestroyed = nullptr;
	UPROPERTY(Transient, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> YourSatellitesDestroyed = nullptr;
	UPROPERTY(Transient, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TotalSatellitesDestroyed = nullptr;
	UPROPERTY(Transient, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> PlayAgainButton = nullptr;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
};
