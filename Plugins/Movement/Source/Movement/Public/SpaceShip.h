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
class MOVEMENT_API ASpaceShip : public APawn
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

public:
    ASpaceShip();

    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent* InPlayerInputComponent) override;

    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
};
