#include "AGCGameState.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"
#include "SpaceShip.h"
#include "Blueprint/UserWidget.h"

AAGCGameState::AAGCGameState()
{
    PrimaryActorTick.bCanEverTick = true;
}

FString AAGCGameState::GetTimerString() const
{
    int32 Minutes = CurrentTimer / 60;
    int32 Seconds = (int32)CurrentTimer % 60;
    return FString::Printf(TEXT("%d:%02d"), Minutes, Seconds);
}

void AAGCGameState::ResetState()
{
    if (!HasAuthority())
        return;

    CurrentTimer = InitialTimer;
    for (APlayerState* PlayerState : PlayerArray)
        if (ASpaceShip* SpaceShip = Cast<ASpaceShip>(PlayerState->GetPawn()))
            SpaceShip->ResetState();

    bIsInEndGame = false;
    OnRep_IsInEndGame();
}

void AAGCGameState::BeginPlay()
{
    Super::BeginPlay();
    if (HasAuthority())
        CurrentTimer = InitialTimer;
}

void AAGCGameState::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (HasAuthority() && CurrentTimer > 0)
    {
        CurrentTimer = FMath::Max(0, CurrentTimer - DeltaTime);
        if (CurrentTimer <= 0)
        {
            bIsInEndGame = true;
            OnRep_IsInEndGame();
        }
    }
}

void AAGCGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AAGCGameState, CurrentTimer);
    DOREPLIFETIME_CONDITION_NOTIFY(AAGCGameState, bIsInEndGame, COND_None, REPNOTIFY_OnChanged);
}

void AAGCGameState::AddPlayerState(APlayerState* NewPlayerState)
{
    Super::AddPlayerState(NewPlayerState);
    OnPlayerStateAdded.Broadcast();
}

void AAGCGameState::OnRep_IsInEndGame()
{
    if (bIsInEndGame)
    {
        EndGameUI = Cast<UUserWidget>(UUserWidget::CreateWidgetInstance(*GetWorld(), EndGameUIClass, NAME_None));
        if (EndGameUI)
            EndGameUI->AddToViewport(10);
    }
    else
    {
        if (EndGameUI)
            EndGameUI->RemoveFromParent();
    }
}