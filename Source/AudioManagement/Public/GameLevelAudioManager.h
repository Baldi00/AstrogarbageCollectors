#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "fmod_studio.hpp"
#include "GameLevelAudioManager.generated.h"

class USpaceShipMovementComponent;
class UFMODEvent;

UCLASS()
class AUDIOMANAGEMENT_API AGameLevelAudioManager : public AActor
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AudioManager")
    TObjectPtr<UFMODEvent> RechargeSound;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AudioManager")
    TObjectPtr<UFMODEvent> LaserRaySound;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AudioManager")
    TObjectPtr<UFMODEvent> DestroyDecomopserSound;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AudioManager")
    TObjectPtr<UFMODEvent> AlarmSoundSound;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AudioManager")
    TObjectPtr<UFMODEvent> ItemCollectedSound;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AudioManager")
    TObjectPtr<UFMODEvent> BackgroundMusic;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AudioManager")
    TObjectPtr<UFMODEvent> RocketSound;

public:
    AGameLevelAudioManager();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    void SetBindings();
    void ResetBindings();

    UFUNCTION()
    void PlayRechargeSound();
    UFUNCTION()
    void PlayLaserRaySound();
    UFUNCTION()
    void PlayDestroyDecomopserSound();
    UFUNCTION()
    void PlayAlarmSound();
    UFUNCTION()
    void PlayItemCollectedSound(int32 CurrentItemCount);

    void PlayBackgroundMusic();
    void PlayRocketSound();
    void UpdateRocketVolume();

    FMOD::Studio::EventInstance* PlayFMOD2DEvent(UFMODEvent* Event);

private:
    USpaceShipMovementComponent* MovementComponent;
    FMOD::Studio::EventInstance* RocketSoundEventInstance;
};
