#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpaceShip.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class USpaceShipMovementComponent;
class UNiagaraComponent;

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class PLAYER_API ASpaceShip : public APawn
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
    TObjectPtr<UNiagaraComponent> FireRocketComponent1;

    UPROPERTY(Category = SpaceShip, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UNiagaraComponent> FireRocketComponent2;

    UPROPERTY(Category = SpaceShip, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UNiagaraComponent> FireRocketComponent3;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr <UInputAction> MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr <UInputAction> LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr <UInputAction> StopAction;

    UPROPERTY(ReplicatedUsing = "OnRep_ActorLocation");
    FVector ActorLocation;
    UPROPERTY(ReplicatedUsing = "OnRep_ActorRotation");
    FRotator ActorRotation;

public:
    ASpaceShip();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(UInputComponent* InPlayerInputComponent) override;

    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void DecreaseVelocity(const FInputActionValue& Value);

    UFUNCTION(Server, Unreliable)
    void Server_Move(FVector MovementVector);
    UFUNCTION(Server, Unreliable)
    void Server_Look(FVector2D LookVector);
    UFUNCTION(Server, Unreliable)
    void Server_DecreaseVelocity(bool bInDecreaseVelocity);

protected:
    UFUNCTION()
    void OnRep_ActorLocation();
    UFUNCTION()
    void OnRep_ActorRotation();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
