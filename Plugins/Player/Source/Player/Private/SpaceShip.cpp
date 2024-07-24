#include "SpaceShip.h"

#include "SpaceShipMovementComponent.h"
#include "SpaceShipShootingComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputTriggers.h"
#include "NiagaraComponent.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/KismetMathLibrary.h"

ASpaceShip::ASpaceShip()
{
    PrimaryActorTick.bCanEverTick = true;

    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));

    static FName SphereCollisionProfileName(TEXT("Pawn"));
    SphereComponent->SetCollisionProfileName(SphereCollisionProfileName);

    RootComponent = SphereComponent;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

    static FName MeshCollisionProfileName(TEXT("NoCollision"));

    MeshComponent->SetCollisionProfileName(MeshCollisionProfileName);
    MeshComponent->SetNotifyRigidBodyCollision(false);
    MeshComponent->SetGenerateOverlapEvents(false);

    MeshComponent->SetupAttachment(SphereComponent);

    SpringArmComponent = CreateOptionalDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

    if (SpringArmComponent != nullptr)
    {
        SpringArmComponent->TargetArmLength = 1600.f;
        SpringArmComponent->SocketOffset = FVector(0.f, 0.f, 500.f);
        SpringArmComponent->bDoCollisionTest = false;
        SpringArmComponent->bEnableCameraRotationLag = false;
        SpringArmComponent->bUsePawnControlRotation = false;
        SpringArmComponent->bInheritPitch = false;
        SpringArmComponent->bInheritYaw = false;
        SpringArmComponent->bInheritRoll = false;

        SpringArmComponent->SetupAttachment(SphereComponent);
    }

    CameraComponent = CreateOptionalDefaultSubobject<UCameraComponent>(TEXT("Camera"));

    if (CameraComponent)
        CameraComponent->SetupAttachment(SpringArmComponent);

    MovementComponent = CreateDefaultSubobject<USpaceShipMovementComponent>(TEXT("Movement"));
    ShootingComponent = CreateDefaultSubobject<USpaceShipShootingComponent>(TEXT("Shooting"));

    bUseControllerRotationYaw = false;

    FireRocketComponent1 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FireRocketComponent1"));
    FireRocketComponent2 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FireRocketComponent2"));
    FireRocketComponent3 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FireRocketComponent3"));

    FireRocketComponent1->SetupAttachment(MeshComponent);
    FireRocketComponent2->SetupAttachment(MeshComponent);
    FireRocketComponent3->SetupAttachment(MeshComponent);

    LeftLaserRaySceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("LeftLaserRaySceneComponent"));
    RightLaserRaySceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RightLaserRaySceneComponent"));
    CentralDestroyDecomposerSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CentralDestroyDecomposerSceneComponent"));

    LeftLaserRaySceneComponent->SetupAttachment(MeshComponent);
    RightLaserRaySceneComponent->SetupAttachment(MeshComponent);
    CentralDestroyDecomposerSceneComponent->SetupAttachment(MeshComponent);

    SetReplicateMovement(false);
}

void ASpaceShip::BeginPlay()
{
    Super::BeginPlay();

    if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
            Subsystem->AddMappingContext(DefaultMappingContext, 0);

    if (IsLocallyControlled())
    {
        if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
            PlayerCameraManager = PlayerController->PlayerCameraManager;

        ensureMsgf(PlayerCameraManager != nullptr, TEXT("ASpaceShip::BeginPlay, Actor doesn't have a PlayerCameraManager"));
    }

    FireRocketComponent1->SetFloatParameter("Scale", 60);
    FireRocketComponent2->SetFloatParameter("Scale", 20);
    FireRocketComponent3->SetFloatParameter("Scale", 20);

    ShootingComponent->SetShootingSceneComponents(LeftLaserRaySceneComponent, CentralDestroyDecomposerSceneComponent, RightLaserRaySceneComponent);
}

void ASpaceShip::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (HasAuthority())
    {
        ActorLocation = GetActorLocation();
        ActorRotation = GetActorRotation();
    }
}

void ASpaceShip::SetupPlayerInputComponent(UInputComponent* InPlayerInputComponent)
{
    Super::SetupPlayerInputComponent(InPlayerInputComponent);

    if (!InPlayerInputComponent)
        return;

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InPlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASpaceShip::Move);
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ASpaceShip::Move);

        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASpaceShip::Look);

        EnhancedInputComponent->BindAction(StopAction, ETriggerEvent::Triggered, this, &ASpaceShip::DecreaseVelocity);
        EnhancedInputComponent->BindAction(StopAction, ETriggerEvent::Completed, this, &ASpaceShip::DecreaseVelocity);

        EnhancedInputComponent->BindAction(ShootLaserRaysAction, ETriggerEvent::Started, this, &ASpaceShip::ShootLaserRays);
        EnhancedInputComponent->BindAction(ShootDestroyDecomposerAction, ETriggerEvent::Completed, this, &ASpaceShip::ShootDestroyDecomposer);
    }
}

void ASpaceShip::Move(const FInputActionValue& Value)
{
    MovementComponent->Move(Value.Get<FVector>());
    if (!HasAuthority())
        Server_Move(Value.Get<FVector>());
}

void ASpaceShip::Look(const FInputActionValue& Value)
{
    MovementComponent->Rotate(Value.Get<FVector2D>());
    if (!HasAuthority())
        Server_Look(Value.Get<FVector2D>());

    if (IsLocallyControlled())
    {
        FRotator SpringArmRotation = SpringArmComponent->GetRelativeRotation();
        SpringArmRotation.Add(-Value.Get<FVector2D>().Y, Value.Get<FVector2D>().X, 0);
        SpringArmRotation.Pitch = FMath::Clamp(SpringArmRotation.Pitch, -30.f, 30.f);
        SpringArmRotation.Roll = 0;
        SpringArmComponent->SetRelativeRotation(SpringArmRotation);
    }
}

void ASpaceShip::DecreaseVelocity(const FInputActionValue& Value)
{
    MovementComponent->DecreaseVelocity(Value.Get<bool>());
    if (!HasAuthority())
        Server_DecreaseVelocity(Value.Get<bool>());
}

void ASpaceShip::ShootLaserRays(const FInputActionValue& Value)
{
    if (!PlayerCameraManager)
        return;

    FRotator BulletsRotation = UKismetMathLibrary::FindLookAtRotation(PlayerCameraManager->GetCameraLocation(),
        PlayerCameraManager->GetCameraLocation() + PlayerCameraManager->GetActorForwardVector());

    if (HasAuthority())
        ShootingComponent->ShootLaserRays(BulletsRotation);
    else
        Server_ShootLaserRays(BulletsRotation);
}

void ASpaceShip::ShootDestroyDecomposer(const FInputActionValue& Value)
{
    if (!PlayerCameraManager)
        return;

    FRotator BulletRotation = UKismetMathLibrary::FindLookAtRotation(PlayerCameraManager->GetCameraLocation(),
        PlayerCameraManager->GetCameraLocation() + PlayerCameraManager->GetActorForwardVector());

    if (HasAuthority())
        ShootingComponent->ShootDestroyDecomposer(BulletRotation);
    else
        Server_ShootDestroyDecomposer(BulletRotation);
}

void ASpaceShip::Server_Move_Implementation(FVector MovementVector)
{
    MovementComponent->Move(MovementVector);
}

void ASpaceShip::Server_Look_Implementation(FVector2D LookVector)
{
    MovementComponent->Rotate(LookVector);
}

void ASpaceShip::Server_DecreaseVelocity_Implementation(bool bInDecreaseVelocity)
{
    MovementComponent->DecreaseVelocity(bInDecreaseVelocity);
}

void ASpaceShip::Server_ShootLaserRays_Implementation(FRotator BulletsRotation)
{
    ShootingComponent->ShootLaserRays(BulletsRotation);
}

void ASpaceShip::Server_ShootDestroyDecomposer_Implementation(FRotator BulletRotation)
{
    ShootingComponent->ShootDestroyDecomposer(BulletRotation);
}

void ASpaceShip::OnRep_ActorLocation()
{
    if (!HasAuthority() && (!IsLocallyControlled() || FVector::DistSquared(GetActorLocation(), ActorLocation) > 10000))
        SetActorLocation(ActorLocation);
}

void ASpaceShip::OnRep_ActorRotation()
{
    if (!HasAuthority() && !IsLocallyControlled())
        SetActorRotation(ActorRotation);
}

void ASpaceShip::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME_CONDITION_NOTIFY(ASpaceShip, ActorLocation, COND_None, REPNOTIFY_OnChanged);
    DOREPLIFETIME_CONDITION_NOTIFY(ASpaceShip, ActorRotation, COND_None, REPNOTIFY_OnChanged);
}