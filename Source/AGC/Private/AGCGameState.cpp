#include "AGCGameState.h"
#include "ABLog.h"
#include "Net/UnrealNetwork.h"
#include <Kismet/KismetSystemLibrary.h>

AAGCGameState::AAGCGameState()
{
    PrimaryActorTick.bCanEverTick = true;
}

FString AAGCGameState::GetTimerString()
{
    int32 Minutes = CurrentTimer / 60;
    int32 Seconds = (int32)CurrentTimer % 60;
    return { STRF("%d:%02d", Minutes, Seconds) };
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
