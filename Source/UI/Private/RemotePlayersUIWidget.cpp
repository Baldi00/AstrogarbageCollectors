#include "RemotePlayersUIWidget.h"
#include "Kismet/GameplayStatics.h"
#include "AGCGameState.h"
#include "GameFramework/PlayerState.h"
#include "Components/VerticalBox.h"
#include <ABDebug.h>

void URemotePlayersUIWidget::NativeConstruct()
{
    Cast<AAGCGameState>(UGameplayStatics::GetGameState(this))->OnPlayerStateAdded.AddUniqueDynamic(this, &URemotePlayersUIWidget::PlayerStateAdded);
}

void URemotePlayersUIWidget::PlayerStateAdded()
{
    RecreateRemotePlayerStatesList();
}

void URemotePlayersUIWidget::RecreateRemotePlayerStatesList()
{
    if (!RemotePlayerUIClass)
        return;

    if (GetWorld()->GetTimerManager().TimerExists(WaitForOwnedPlayerStateTimerHandle))
        GetWorld()->GetTimerManager().ClearTimer(WaitForOwnedPlayerStateTimerHandle);

    APlayerState* MyPlayerState = GetOwningPlayerPawn()->GetPlayerState();
    if (MyPlayerState == nullptr)
    {
        GetWorld()->GetTimerManager().SetTimer(WaitForOwnedPlayerStateTimerHandle, FTimerDelegate::CreateUFunction(this, "CheckForOwningPlayerState"), 0.5f, true);
        return;
    }

    TArray<TObjectPtr<APlayerState>> PlayerStates = UGameplayStatics::GetGameState(this)->PlayerArray;

    VerticalBox->ClearChildren();
    int32 Count = 2;
    for (int i = 0; i < PlayerStates.Num(); i++)
    {
        if (PlayerStates[i] == MyPlayerState)
            continue;

        URemotePlayerUIWidget* RemotePlayerWidget = CreateWidget<URemotePlayerUIWidget>(GetOwningPlayer(), RemotePlayerUIClass);
        RemotePlayerWidget->SetPadding(FMargin(0, 0, 0, VerticalBoxSpacing));
        RemotePlayerWidget->SetPlayerState(PlayerStates[i]);
        RemotePlayerWidget->SetPlayerName(FString::Printf(TEXT("Player %d"), Count));
        VerticalBox->AddChildToVerticalBox(RemotePlayerWidget);
        Count++;
    }
}

void URemotePlayersUIWidget::CheckForOwningPlayerState()
{
    if (GetOwningPlayerPawn()->GetPlayerState() != nullptr)
        RecreateRemotePlayerStatesList();
}