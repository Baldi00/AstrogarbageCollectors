#include "Checkpoint.h"
#include "Components/SphereComponent.h"

ACheckpoint::ACheckpoint()
{
    Tags.AddUnique("Checkpoint");

    SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
    static FName SphereColliderCollisionProfileName = TEXT("OverlapAll");
    SphereCollider->SetCollisionProfileName(SphereColliderCollisionProfileName);
    SphereCollider->SetupAttachment(RootComponent);
}