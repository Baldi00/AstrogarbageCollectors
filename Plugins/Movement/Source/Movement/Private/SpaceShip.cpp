#include "SpaceShip.h"

#include "SpaceShipMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputTriggers.h"
#include "NiagaraComponent.h"

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
        SpringArmComponent->bUsePawnControlRotation = true;
        SpringArmComponent->bInheritPitch = true;
        SpringArmComponent->bInheritYaw = true;
        SpringArmComponent->bInheritRoll = false;

        SpringArmComponent->SetupAttachment(SphereComponent);
    }

    CameraComponent = CreateOptionalDefaultSubobject<UCameraComponent>(TEXT("Camera"));

    if (CameraComponent)
        CameraComponent->SetupAttachment(SpringArmComponent);

    MovementComponent = CreateDefaultSubobject<USpaceShipMovementComponent>(TEXT("Movement"));

    bUseControllerRotationYaw = true;

    FireRocketComponent1 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FireRocketComponent1"));
    FireRocketComponent2 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FireRocketComponent2"));
    FireRocketComponent3 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FireRocketComponent3"));

    FireRocketComponent1->SetupAttachment(MeshComponent);
    FireRocketComponent2->SetupAttachment(MeshComponent);
    FireRocketComponent3->SetupAttachment(MeshComponent);
}

void ASpaceShip::BeginPlay()
{
    Super::BeginPlay();

    if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
            Subsystem->AddMappingContext(DefaultMappingContext, 0);

    FireRocketComponent1->SetFloatParameter("Scale", 60);
    FireRocketComponent2->SetFloatParameter("Scale", 20);
    FireRocketComponent3->SetFloatParameter("Scale", 20);
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
    }
}

void ASpaceShip::Move(const FInputActionValue& Value)
{
    MovementComponent->Move(Value.Get<FVector>());
}

void ASpaceShip::Look(const FInputActionValue& Value)
{
    MovementComponent->Look(Value.Get<FVector2D>());
}