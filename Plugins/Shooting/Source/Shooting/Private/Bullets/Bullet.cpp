#include "Bullets/Bullet.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

ABullet::ABullet()
{
    DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
    RootComponent = DefaultSceneRoot;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

    static FName MeshCollisionProfileName(TEXT("NoCollision"));
    Mesh->SetCollisionProfileName(MeshCollisionProfileName);
    Mesh->SetNotifyRigidBodyCollision(false);
    Mesh->SetGenerateOverlapEvents(false);

    Mesh->SetupAttachment(RootComponent);

    bReplicates = true;
    PrimaryActorTick.bCanEverTick = true;
}

void ABullet::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        SetLifeSpan(LifeTime);
        LineTraceQueryParams.AddIgnoredActor(this);
    }
}

void ABullet::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    StepForward(DeltaTime);
}

void ABullet::AddCollisionIgnoredActor(AActor* InIgnoredActor)
{
    LineTraceQueryParams.AddIgnoredActor(InIgnoredActor);
}

void ABullet::StepForward(float DeltaTime)
{
    NextLocation = GetActorLocation() + DeltaTime * Speed * GetActorForwardVector();

    if (HasAuthority())
        CheckCollisionsBetweenPreviousAndNextLocations();

    SetActorLocation(NextLocation);
}

void ABullet::CheckCollisionsBetweenPreviousAndNextLocations()
{
    if (HasAuthority())
    {
        if (GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation(), NextLocation, ECC_Visibility, LineTraceQueryParams))
            OnCollisionHappened();
    }
}

void ABullet::OnCollisionHappened()
{
}