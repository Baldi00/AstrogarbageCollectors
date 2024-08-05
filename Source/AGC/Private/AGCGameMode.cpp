#include "AGCGameMode.h"
#include "AGCGameState.h"

void AAGCGameMode::ResetGame()
{
    GetGameState<AAGCGameState>()->ResetState();
}
