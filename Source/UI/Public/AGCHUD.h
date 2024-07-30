#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LocalPlayerUIWidget.h"
#include "RemotePlayersUIWidget.h"
#include "AGCHUD.generated.h"

UCLASS()
class UI_API AAGCHUD : public AHUD
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULocalPlayerUIWidget> LocalPlayerUIClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URemotePlayersUIWidget> RemotePlayersUIClass;

	TObjectPtr<ULocalPlayerUIWidget> LocalPlayerUIWidget;
	TObjectPtr<URemotePlayersUIWidget> RemotePlayersUIWidget;

protected:
	virtual void BeginPlay() override;
};
