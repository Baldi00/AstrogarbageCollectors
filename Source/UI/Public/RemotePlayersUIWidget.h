#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RemotePlayerUIWidget.h"
#include "RemotePlayersUIWidget.generated.h"

class UVerticalBox;

UCLASS()
class UI_API URemotePlayersUIWidget : public UUserWidget
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<URemotePlayerUIWidget> RemotePlayerUIClass;

protected:
    UPROPERTY(Transient, BlueprintReadOnly, meta = (BindWidget), DisplayName = "Vertical Box")
    TObjectPtr<UVerticalBox> VerticalBox = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float VerticalBoxSpacing = 50;
    
    virtual void NativeConstruct() override;

    UFUNCTION()
    void PlayerStateAdded();

    UFUNCTION()
    void RecreateRemotePlayerStatesList();

private:
    // Due to unknown owned player state receive moment I set a timer that periodically checks if player state has been set
    FTimerHandle WaitForOwnedPlayerStateTimerHandle;
    UFUNCTION()
    void CheckForOwningPlayerState();
};
