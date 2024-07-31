#include "AGCGameState.h"
#include "Net/UnrealNetwork.h"

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
            OnTimerEnded.Broadcast();
    }
}

void AAGCGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AAGCGameState, CurrentTimer);
}
