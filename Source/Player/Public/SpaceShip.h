#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Rechargeable.h"
#include "SpaceShip.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class USpaceShipMovementComponent;
class USpaceShipShootingComponent;
class USpaceShipRechargerComponent;
class UNiagaraComponent;
class USceneComponent;

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStateReceived, APlayerState*, PlayerState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRecharged);

UCLASS()
class PLAYER_API ASpaceShip : public APawn, public IRechargeable
{
    GENERATED_BODY()

    UPROPERTY(Category = SpaceShip, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USphereComponent> SphereComponent;

    UPROPERTY(Category = SpaceShip, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UStaticMeshComponent> MeshComponent;

    UPROPERTY(Category = SpaceShip, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USpringArmComponent> SpringArmComponent;

    UPROPERTY(Category = SpaceShip, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UCameraComponent> CameraComponent;

    UPROPERTY(Category = SpaceShip, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USpaceShipMovementComponent> MovementComponent;

    UPROPERTY(Category = SpaceShip, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USpaceShipShootingComponent> ShootingComponent;

    UPROPERTY(Category = SpaceShip, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USpaceShipRechargerComponent> RechargerComponent;

    UPROPERTY(Category = SpaceShip, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UNiagaraComponent> FireRocketComponent1;

    UPROPERTY(Category = SpaceShip, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UNiagaraComponent> FireRocketComponent2;

    UPROPERTY(Category = SpaceShip, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UNiagaraComponent> FireRocketComponent3;

    UPROPERTY(Category = SpaceShip, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USceneComponent> LeftLaserRaySceneComponent;

    UPROPERTY(Category = SpaceShip, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USceneComponent> RightLaserRaySceneComponent;

    UPROPERTY(Category = SpaceShip, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USceneComponent> CentralDestroyDecomposerSceneComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr <UInputAction> MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr <UInputAction> LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr <UInputAction> StopAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr <UInputAction> ShootLaserRaysAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr <UInputAction> ShootDestroyDecomposerAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr <UInputAction> RelocateAction;

    UPROPERTY(ReplicatedUsing = "OnRep_ActorLocation");
    FVector ActorLocation;
    UPROPERTY(ReplicatedUsing = "OnRep_ActorRotation");
    FRotator ActorRotation;

    APlayerCameraManager* PlayerCameraManager;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = SpaceShip, meta = (AllowPrivateAccess = "true"))
    float CanRechargeCooldown = 2;
    float CanRechargeTimer = 0;

    FVector StartingPosition;

public:
    ASpaceShip();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(UInputComponent* InPlayerInputComponent) override;
    virtual void Restart() override;

    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void DecreaseVelocity(const FInputActionValue& Value);
    void ShootLaserRays(const FInputActionValue& Value);
    void ShootDestroyDecomposer(const FInputActionValue& Value);
    void Relocate(const FInputActionValue& Value);

    void ResetState();

    UFUNCTION(Server, Unreliable)
    void Server_Move(FVector MovementVector);
    UFUNCTION(Server, Unreliable)
    void Server_Look(FVector2D LookVector);
    UFUNCTION(Server, Unreliable)
    void Server_DecreaseVelocity(bool bInDecreaseVelocity);
    UFUNCTION(Server, Reliable)
    void Server_ShootLaserRays(FRotator BulletsRotation);
    UFUNCTION(Server, Reliable)
    void Server_ShootDestroyDecomposer(FRotator BulletRotation);
    UFUNCTION(Server, Reliable)
    void Server_Relocate();
    UFUNCTION(Server, Reliable)
    void Server_Recharge();
    UFUNCTION(Server, Reliable)
    void Server_ResetState();

    virtual void Recharge() override;

    UFUNCTION(BlueprintImplementableEvent)
    void SpawnRechargeVFX();

    USpaceShipMovementComponent* GetSpaceShipMovementComponent() const { return MovementComponent; }

    FOnPlayerStateReceived OnPlayerStateReceived;

    UPROPERTY(BlueprintAssignable)
    FOnRecharged OnRecharged;

protected:
    UFUNCTION()
    void OnRep_ActorLocation();
    UFUNCTION()
    void OnRep_ActorRotation();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    virtual void OnPlayerStateChanged(APlayerState* NewPlayerState, APlayerState* OldPlayerState) override;

};
