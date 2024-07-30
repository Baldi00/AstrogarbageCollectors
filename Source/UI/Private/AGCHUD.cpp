#include "AGCHUD.h"

void AAGCHUD::BeginPlay()
{
    Super::BeginPlay();
    if (LocalPlayerUIClass)
    {
        LocalPlayerUIWidget = CreateWidget<ULocalPlayerUIWidget>(GetWorld(), LocalPlayerUIClass);
        LocalPlayerUIWidget->AddToViewport();
    }
    if (RemotePlayersUIClass)
    {
        RemotePlayersUIWidget = CreateWidget<URemotePlayersUIWidget>(GetWorld(), RemotePlayersUIClass);
        RemotePlayersUIWidget->AddToViewport();
    }
}
