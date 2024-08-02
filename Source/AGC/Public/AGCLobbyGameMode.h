#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AGCLobbyGameMode.generated.h"

UCLASS()
class AGC_API AAGCLobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void InitGameState() override;
	virtual void OnPostLogin(AController* NewPlayer) override;

protected:
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> GameMap;

private:

	void Travel();
	bool CanTravel();
};
