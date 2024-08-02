#include "AGCLobbyGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ABDebug.h"
#include "AGCLobbyGameState.h"

void AAGCLobbyGameMode::InitGameState()
{
    Super::InitGameState();

    AAGCLobbyGameState* LobbyGameState{ GetGameState<AAGCLobbyGameState>() };
    if (!IsValid(LobbyGameState))
    {
        LOG("AAGCLobbyGameState is invalid.");
        return;
    }

    // OptionsString store any Option we received from the Relative Travel we made.
    const FString MaxPlayersOption{ TEXT("MaxPlayers") };
    if (!UGameplayStatics::HasOption(OptionsString, MaxPlayersOption))
    {
        LOG("MaxPlayers option is not found in Options.");
        return;
    }

    const FString MaxPlayersValueAsString{ UGameplayStatics::ParseOption(OptionsString, MaxPlayersOption) };
    if (!MaxPlayersValueAsString.IsNumeric())
        LOGF("%s option is not a numeric value.", *MaxPlayersOption);

    LobbyGameState->MaxPlayers = FCString::Atoi(*MaxPlayersValueAsString);
}

void AAGCLobbyGameMode::OnPostLogin(AController* NewPlayer)
{
    Super::OnPostLogin(NewPlayer);

    if (!CanTravel())
        return;

    Travel();
}

void AAGCLobbyGameMode::Travel()
{
    if (GameMap.IsNull())
        return;

    GetWorld()->ServerTravel(GameMap.GetLongPackageName(), false);
}

bool AAGCLobbyGameMode::CanTravel()
{
    const AAGCLobbyGameState* LobbyGameState{ GetGameState<AAGCLobbyGameState>() };
    if (!IsValid(LobbyGameState))
    {
        LOG("AAGCLobbyGameState is invalid.");
        return false;
    }

    return GetNumPlayers() == LobbyGameState->MaxPlayers;
}