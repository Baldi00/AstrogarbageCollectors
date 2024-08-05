#include "EndGameUIWidget.h"
#include "AGCGameState.h"
#include "AGCGameMode.h"
#include "SpaceShipPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UEndGameUIWidget::NativeConstruct()
{
    AAGCGameState* GameState = Cast<AAGCGameState>(UGameplayStatics::GetGameState(this));

    if (!GameState)
        return;

    int32 MyAsteroidsDestroyedCount = 0;
    int32 TotalAsteroidsDestroyedCount = 0;
    int32 MySatellitesDestroyedCount = 0;
    int32 TotalSatellitesDestroyedCount = 0;

    for (APlayerState* PlayerState : GameState->PlayerArray)
    {
        if (ASpaceShipPlayerState* SpaceShipPlayerState = Cast<ASpaceShipPlayerState>(PlayerState))
        {
            TotalAsteroidsDestroyedCount += SpaceShipPlayerState->GetAsteroidsDestroyed();
            if (SpaceShipPlayerState->GetPawn()->IsLocallyControlled())
                MyAsteroidsDestroyedCount = SpaceShipPlayerState->GetAsteroidsDestroyed();

            TotalSatellitesDestroyedCount += SpaceShipPlayerState->GetSatellitesDestroyed();
            if (SpaceShipPlayerState->GetPawn()->IsLocallyControlled())
                MySatellitesDestroyedCount = SpaceShipPlayerState->GetSatellitesDestroyed();
        }
    }

    YourAsteroidsDestroyed->SetText(FText::FromString(FString::FromInt(MyAsteroidsDestroyedCount)));
    TotalAsteroidsDestroyed->SetText(FText::FromString(FString::FromInt(TotalAsteroidsDestroyedCount)));
    YourSatellitesDestroyed->SetText(FText::FromString(FString::FromInt(MySatellitesDestroyedCount)));
    TotalSatellitesDestroyed->SetText(FText::FromString(FString::FromInt(TotalSatellitesDestroyedCount)));

    if (GameState->HasAuthority())
        PlayAgainButton->OnClicked.AddUniqueDynamic(Cast<AAGCGameMode>(UGameplayStatics::GetGameMode(this)), &AAGCGameMode::ResetGame);
    else
        PlayAgainButton->SetVisibility(ESlateVisibility::Collapsed);

    UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(UGameplayStatics::GetPlayerController(this, 0));
    UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(true);
}

void UEndGameUIWidget::NativeDestruct()
{
    PlayAgainButton->OnClicked.Clear();
    UWidgetBlueprintLibrary::SetInputMode_GameOnly(UGameplayStatics::GetPlayerController(this, 0));
    UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(false);
}