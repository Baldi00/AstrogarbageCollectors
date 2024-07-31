#include "LocalPlayerUIWidget.h"
#include "SpaceShip.h"
#include "SpaceShipMovementComponent.h"
#include "SpaceShipShootingComponent.h"
#include "SpaceShipPlayerState.h"
#include "AGCGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void ULocalPlayerUIWidget::NativeConstruct()
{
    Super::NativeConstruct();
    SetBindings();

    if (MovementComponent.IsValid())
        UpdateFuelBar(MovementComponent->GetCurrentFuelLevel());
    if (ShootingComponent.IsValid())
        UpdateAmmoCount(ShootingComponent->GetLaserRayAmmoCount(), ShootingComponent->GetDestroyDecomposerAmmoCount());
}

void ULocalPlayerUIWidget::NativeDestruct()
{
    ResetBindings();
    Super::NativeDestruct();
}

void ULocalPlayerUIWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    if (GameState.IsValid())
        UpdateTimer(GameState->GetTimerString());
    if (!PlayerState.IsValid())
        SetPlayerStateBinding();
}

void ULocalPlayerUIWidget::SetBindings()
{
    ResetBindings();

    APawn* Pawn = GetOwningPlayerPawn();
    ensureMsgf(Pawn != nullptr, TEXT("ULocalPlayerUIWidget::SetBindings: Owning Pawn not found"));
    ensureMsgf(Pawn->IsA<ASpaceShip>(), TEXT("ULocalPlayerUIWidget::SetBindings: Owning Pawn isn't of type ASpaceShip"));

    MovementComponent = MakeWeakObjectPtr(Pawn->FindComponentByClass<USpaceShipMovementComponent>());
    ShootingComponent = MakeWeakObjectPtr(Pawn->FindComponentByClass<USpaceShipShootingComponent>());
    GameState = MakeWeakObjectPtr(Cast<AAGCGameState>(UGameplayStatics::GetGameState(this)));

    MovementComponent->OnFuelLevelUpdated.AddUniqueDynamic(this, &ULocalPlayerUIWidget::UpdateFuelBar);
    ShootingComponent->OnAmmoUpdated.AddUniqueDynamic(this, &ULocalPlayerUIWidget::UpdateAmmoCount);

    SetPlayerStateBinding();
}

void ULocalPlayerUIWidget::ResetBindings()
{
    if (MovementComponent.IsValid())
    {
        MovementComponent->OnFuelLevelUpdated.RemoveDynamic(this, &ULocalPlayerUIWidget::UpdateFuelBar);
        MovementComponent.Reset();
    }
    if (ShootingComponent.IsValid())
    {
        ShootingComponent->OnAmmoUpdated.RemoveDynamic(this, &ULocalPlayerUIWidget::UpdateAmmoCount);
        ShootingComponent.Reset();
    }
    if (PlayerState.IsValid())
    {
        PlayerState->OnDestroyedAsteroidsCountUpdated.RemoveDynamic(this, &ULocalPlayerUIWidget::UpdateDestroyedAsteroidsCount);
        PlayerState->OnDestroyedSatellitesCountUpdated.RemoveDynamic(this, &ULocalPlayerUIWidget::UpdateDestroyedSatellitesCount);
        PlayerState.Reset();
    }
    if (GameState.IsValid())
        GameState.Reset();
}

void ULocalPlayerUIWidget::SetPlayerStateBinding()
{
    PlayerState = MakeWeakObjectPtr(Cast<ASpaceShipPlayerState>(GetOwningPlayerPawn()->GetPlayerState()));
    if (PlayerState.IsValid())
    {
        PlayerState->OnDestroyedAsteroidsCountUpdated.AddUniqueDynamic(this, &ULocalPlayerUIWidget::UpdateDestroyedAsteroidsCount);
        PlayerState->OnDestroyedSatellitesCountUpdated.AddUniqueDynamic(this, &ULocalPlayerUIWidget::UpdateDestroyedSatellitesCount);
    }
}

void ULocalPlayerUIWidget::UpdateFuelBar(float InCurrentFuelLevel)
{
    FuelBar->SetPercent(InCurrentFuelLevel / 100);
}

void ULocalPlayerUIWidget::UpdateTimer(const FString& InCurrentTimerString)
{
    Timer->SetText(FText::FromString(InCurrentTimerString));
}

void ULocalPlayerUIWidget::UpdateAmmoCount(int32 InCurrentLaserRayAmmoCount, int32 InCurrentDestroyDecomposerAmmoCount)
{
    LaserRayAmmoCount->SetText(FText::FromString(FString::Printf(TEXT("%02d"), InCurrentLaserRayAmmoCount)));
    DestroyDecomposerAmmoCount->SetText(FText::FromString(FString::Printf(TEXT("%02d"), InCurrentDestroyDecomposerAmmoCount)));
}

void ULocalPlayerUIWidget::UpdateDestroyedAsteroidsCount(int32 InCurrentDestroyedAsteroidsCount)
{
    DestroyedAsteroidsCount->SetText(FText::FromString(FString::Printf(TEXT("%02d"), InCurrentDestroyedAsteroidsCount)));
}

void ULocalPlayerUIWidget::UpdateDestroyedSatellitesCount(int32 InCurrentDestroyedSatellitesCount)
{
    DestroyedSatellitesCount->SetText(FText::FromString(FString::Printf(TEXT("%02d"), InCurrentDestroyedSatellitesCount)));
}
