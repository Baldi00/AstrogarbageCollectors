#include "GameLevelAudioManager.h"
#include "Kismet/GameplayStatics.h"
#include "SpaceShip.h"
#include "SpaceShipShootingComponent.h"
#include "SpaceShipMovementComponent.h"
#include "SpaceShipPlayerState.h"
#include "FMODBlueprintStatics.h"

AGameLevelAudioManager::AGameLevelAudioManager()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AGameLevelAudioManager::BeginPlay()
{
    Super::BeginPlay();
    SetBindings();
    PlayBackgroundMusic();
    PlayRocketSound();
}

void AGameLevelAudioManager::Tick(float DeltaTime)
{
    UpdateRocketVolume();
}

void AGameLevelAudioManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    ResetBindings();
    Super::EndPlay(EndPlayReason);
}

void AGameLevelAudioManager::SetBindings()
{
    ASpaceShip* SpaceShip = Cast<ASpaceShip>(UGameplayStatics::GetPlayerPawn(this, 0));

    if (SpaceShip)
    {
        SpaceShip->OnRecharged.AddUniqueDynamic(this, &AGameLevelAudioManager::PlayRechargeSound);

        USpaceShipShootingComponent* ShootingComponent = SpaceShip->GetComponentByClass<USpaceShipShootingComponent>();
        if (ShootingComponent)
        {
            ShootingComponent->OnLaserRaysShooted.AddUniqueDynamic(this, &AGameLevelAudioManager::PlayLaserRaySound);
            ShootingComponent->OnDestroyDecomposerShooted.AddUniqueDynamic(this, &AGameLevelAudioManager::PlayDestroyDecomopserSound);
            ShootingComponent->OnTryingToShootEmptyAmmo.AddUniqueDynamic(this, &AGameLevelAudioManager::PlayAlarmSound);
        }

        MovementComponent = SpaceShip->GetComponentByClass<USpaceShipMovementComponent>();
        if (MovementComponent)
        {
            MovementComponent->OnFuelLow.AddUniqueDynamic(this, &AGameLevelAudioManager::PlayAlarmSound);
            MovementComponent->OnFuelEnded.AddUniqueDynamic(this, &AGameLevelAudioManager::PlayAlarmSound);
        }
    }

    ASpaceShipPlayerState* PlayerState = Cast<ASpaceShipPlayerState>(UGameplayStatics::GetPlayerState(this, 0));

    if (PlayerState)
    {
        PlayerState->OnDestroyedAsteroidsCountUpdated.AddUniqueDynamic(this, &AGameLevelAudioManager::PlayItemCollectedSound);
        PlayerState->OnDestroyedSatellitesCountUpdated.AddUniqueDynamic(this, &AGameLevelAudioManager::PlayItemCollectedSound);
    }
}

void AGameLevelAudioManager::ResetBindings()
{
    ASpaceShip* SpaceShip = Cast<ASpaceShip>(UGameplayStatics::GetPlayerPawn(this, 0));

    if (SpaceShip)
    {
        SpaceShip->OnRecharged.RemoveDynamic(this, &AGameLevelAudioManager::PlayRechargeSound);

        USpaceShipShootingComponent* ShootingComponent = SpaceShip->GetComponentByClass<USpaceShipShootingComponent>();
        if (ShootingComponent)
        {
            ShootingComponent->OnLaserRaysShooted.RemoveDynamic(this, &AGameLevelAudioManager::PlayLaserRaySound);
            ShootingComponent->OnDestroyDecomposerShooted.RemoveDynamic(this, &AGameLevelAudioManager::PlayDestroyDecomopserSound);
            ShootingComponent->OnTryingToShootEmptyAmmo.RemoveDynamic(this, &AGameLevelAudioManager::PlayAlarmSound);
        }

        if (MovementComponent)
        {
            MovementComponent->OnFuelLow.RemoveDynamic(this, &AGameLevelAudioManager::PlayAlarmSound);
            MovementComponent->OnFuelEnded.AddUniqueDynamic(this, &AGameLevelAudioManager::PlayAlarmSound);
        }
    }

    ASpaceShipPlayerState* PlayerState = Cast<ASpaceShipPlayerState>(UGameplayStatics::GetPlayerState(this, 0));

    if (PlayerState)
    {
        PlayerState->OnDestroyedAsteroidsCountUpdated.RemoveDynamic(this, &AGameLevelAudioManager::PlayItemCollectedSound);
        PlayerState->OnDestroyedSatellitesCountUpdated.RemoveDynamic(this, &AGameLevelAudioManager::PlayItemCollectedSound);
    }
}

void AGameLevelAudioManager::PlayRechargeSound()
{
    PlayFMOD2DEvent(RechargeSound);
}

void AGameLevelAudioManager::PlayLaserRaySound()
{
    PlayFMOD2DEvent(LaserRaySound);
}

void AGameLevelAudioManager::PlayDestroyDecomopserSound()
{
    PlayFMOD2DEvent(DestroyDecomopserSound);
}

void AGameLevelAudioManager::PlayAlarmSound()
{
    PlayFMOD2DEvent(AlarmSoundSound);
}

void AGameLevelAudioManager::PlayItemCollectedSound(int32 CurrentItemCount)
{
    PlayFMOD2DEvent(ItemCollectedSound);
}

void AGameLevelAudioManager::PlayBackgroundMusic()
{
    PlayFMOD2DEvent(BackgroundMusic);
}

void AGameLevelAudioManager::PlayRocketSound()
{
    RocketSoundEventInstance = PlayFMOD2DEvent(RocketSound);
}

void AGameLevelAudioManager::UpdateRocketVolume()
{
    if (!MovementComponent || !RocketSoundEventInstance)
        return;

    float CurrentRocketPower = 0;
    if (MovementComponent->GetForwardInputSmoothedPercentage() > 0.3f)
        CurrentRocketPower = MovementComponent->GetForwardInputSmoothedPercentage();
    else if (MovementComponent->GetCurrentMovementVector() != FVector::ZeroVector ||
        (MovementComponent->ShouldDecreaseVelocity() && MovementComponent->GetSpaceShipVelocity().SquaredLength() > 25))
        CurrentRocketPower = 0.3f;

    RocketSoundEventInstance->setParameterByName("RocketPower", CurrentRocketPower);
}

FMOD::Studio::EventInstance* AGameLevelAudioManager::PlayFMOD2DEvent(UFMODEvent* Event)
{
    FFMODEventInstance InstanceWrapper = UFMODBlueprintStatics::PlayEvent2D(this, Event, true);
    return InstanceWrapper.Instance;
}

