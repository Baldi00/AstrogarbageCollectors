#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "Rechargeable.h"
#include "SpaceShipMovementComponent.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UNiagaraComponent;
class ISpaceShipPlayerStateInterface;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFuelLevelUpdated, float, InCurrentFuelLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFuelLow);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFuelEnded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFuelRecharged);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MOVEMENT_API USpaceShipMovementComponent : public UMovementComponent, public IRechargeable
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float MaxSpeed = 75;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float Acceleration = 30;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float MaxSpeedForward = 150;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float AccelerationForward = 60;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fuel", meta = (AllowPrivateAccess = "true"))
    float MaxFuel = 100;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fuel", meta = (AllowPrivateAccess = "true"))
    float FuelLowThreshold = 30;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fuel", meta = (AllowPrivateAccess = "true"))
    float FuelDecreaseSpeed = 2;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fuel", meta = (AllowPrivateAccess = "true"))
    float FuelDecreaseSpeedForward = 3;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement Effects", meta = (AllowPrivateAccess = "true"))
    float MaxPitchAngle = 4.5f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement Effects", meta = (AllowPrivateAccess = "true"))
    float MaxRollAngle = 7.5f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement Effects", meta = (AllowPrivateAccess = "true"))
    float PitchSpeed = 10;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement Effects", meta = (AllowPrivateAccess = "true"))
    float RollSpeed = 20;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement Effects", meta = (AllowPrivateAccess = "true"))
    float CameraSocketMaxOffset = 75;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement Effects", meta = (AllowPrivateAccess = "true"))
    float CameraSocketOffsetSpeed = 200;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement Effects", meta = (AllowPrivateAccess = "true"))
    float ForwardInputSmoothedMaxDuration = 3;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement Effects", meta = (AllowPrivateAccess = "true"))
    float ForwardInputSmoothedDecaySpeed = 3;

    UPROPERTY(BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    FVector SpaceShipVelocity = FVector::ZeroVector;
    UPROPERTY(Replicated, ReplicatedUsing = "OnRep_ServerSpaceShipVelocity")
    FVector ServerSpaceShipVelocity = FVector::ZeroVector;

    UPROPERTY(Replicated)
    FVector CurrentMovementVector = FVector::ZeroVector;

    float TimeToReachMaxSpeedTimer = 0;
    float DefaultCameraSocketOffset = 500;

    UPROPERTY(BlueprintReadOnly, Category = "Movement Effects", meta = (AllowPrivateAccess = "true"), Replicated)
    float ForwardInputSmoothedTimer = 0;

    bool bDecreaseVelocity = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, ReplicatedUsing = "OnRep_CurrentFuelLevel", meta = (AllowPrivateAccess = "true"))
    float CurrentFuelLevel = 0;

    APawn* Owner = nullptr;
    ISpaceShipPlayerStateInterface* PlayerState = nullptr;
    UStaticMeshComponent* SpaceShipMeshComponent = nullptr;
    USpringArmComponent* SpaceShipSpringArmComponent = nullptr;
    UCameraComponent* SpaceShipCameraComponent = nullptr;
    UNiagaraComponent* FireRocketComponent1 = nullptr;
    UNiagaraComponent* FireRocketComponent2 = nullptr;
    UNiagaraComponent* FireRocketComponent3 = nullptr;
    bool bAlreadyWarnedAboutFuelLow = false;
    bool bAlreadyWarnedAboutFuelEnded = false;
    bool bAlreadyWarnedAboutFuelRecharged = true;

public:
    USpaceShipMovementComponent();

    void OnPossess();
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void Move(const FVector& MovementVector) { CurrentMovementVector = MovementVector; }
    void Rotate(const FVector2D& LookVector);
    void DecreaseVelocity(const bool bInDecreaseVelocity) { bDecreaseVelocity = bInDecreaseVelocity; }
    void Relocate(const FVector& StartingPosition, bool bForceRelocation = false);

    virtual void Recharge() override;

    void SetPlayerState(APlayerState* InPlayerState);
    float GetCurrentFuelLevel() const { return CurrentFuelLevel; }
    FVector GetSpaceShipVelocity() const { return SpaceShipVelocity; }
    float GetMaxSpeedForward() const { return MaxSpeedForward; }
    float GetForwardInputSmoothedPercentage() const { return ForwardInputSmoothedTimer / ForwardInputSmoothedMaxDuration; }
    FVector GetCurrentMovementVector() const { return CurrentMovementVector; }
    bool ShouldDecreaseVelocity() const { return bDecreaseVelocity; }

private:
    void UpdateVelocity(float DeltaTime);
    void UpdateMovementEffects(float DeltaTime);
    void UpdateFireRockets();
    void UpdateSpaceShipRotation(float DeltaTime);
    void UpdateCameraSocketOffset(float DeltaTime);
    void UpdateForwardInputSmoothedTimer(float DeltaTime);
    void SetCurrentFuelLevel(float InCurrentFuelLevel);

protected:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION()
    void OnRep_CurrentFuelLevel();
    UFUNCTION()
    void OnRep_ServerSpaceShipVelocity();

public:
    UPROPERTY(BlueprintAssignable)
    FOnFuelLevelUpdated OnFuelLevelUpdated;
    UPROPERTY(BlueprintAssignable)
    FOnFuelLow OnFuelLow;
    UPROPERTY(BlueprintAssignable)
    FOnFuelEnded OnFuelEnded;
    UPROPERTY(BlueprintAssignable)
    FOnFuelRecharged OnFuelRecharged;
};
