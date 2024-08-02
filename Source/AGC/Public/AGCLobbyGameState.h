#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AGCLobbyGameState.generated.h"

UCLASS()
class AGC_API AAGCLobbyGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	int32 MaxPlayers;
};
