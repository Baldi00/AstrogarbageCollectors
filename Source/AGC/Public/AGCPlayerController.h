#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AGCPlayerController.generated.h"

UCLASS()
class AGC_API AAGCPlayerController : public APlayerController
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

private:
    UFUNCTION(Server, Reliable)
    void Server_ReceivePlayerName(const AAGCPlayerController* PlayerController, const FString& PlayerName);

    void ReceivePlayerName(const AAGCPlayerController* PlayerController, const FString& PlayerName);
};
