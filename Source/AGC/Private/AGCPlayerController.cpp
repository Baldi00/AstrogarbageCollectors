#include "AGCPlayerController.h"
#include "AGCGameInstance.h"
#include "SpaceShipPlayerStateInterface.h"
#include "ABDebug.h"

void AAGCPlayerController::BeginPlay()
{
	Super::BeginPlay();

	const UAGCGameInstance* GameInstance{ GetGameInstance<UAGCGameInstance>() };
	if (!IsValid(GameInstance))
	{
		LOG("GameInstance is invalid.");
		return;
	}

	if (HasAuthority())
		ReceivePlayerName(this, GameInstance->PlayerName);
	else
		Server_ReceivePlayerName(this, GameInstance->PlayerName);
}

void AAGCPlayerController::Server_ReceivePlayerName_Implementation(const AAGCPlayerController* PlayerController, const FString& PlayerName)
{
	ReceivePlayerName(PlayerController, PlayerName);
}

void AAGCPlayerController::ReceivePlayerName(const AAGCPlayerController* PlayerController, const FString& PlayerName)
{
	if (!IsValid(PlayerController))
		return;

	ISpaceShipPlayerStateInterface* SpaceShipPlayerState = PlayerController->GetPlayerState<ISpaceShipPlayerStateInterface>();
	if (!SpaceShipPlayerState)
	{
		LOG("ArenaPlayerState is invalid.");
		return;
	}

	SpaceShipPlayerState->SetSpaceShipName(PlayerName);
}