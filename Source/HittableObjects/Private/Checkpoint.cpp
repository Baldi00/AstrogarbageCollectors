#include "Checkpoint.h"
#include "Components/SphereComponent.h"
#include "Rechargeable.h"

ACheckpoint::ACheckpoint()
{
    Tags.AddUnique("Checkpoint");

    SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
    static FName SphereColliderCollisionProfileName = TEXT("OverlapAll");
    SphereCollider->SetCollisionProfileName(SphereColliderCollisionProfileName);
    SphereCollider->OnComponentBeginOverlap.AddUniqueDynamic(this, &ACheckpoint::RechargeSpaceShip);
    SphereCollider->SetupAttachment(RootComponent);
}

void ACheckpoint::RechargeSpaceShip(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (Other->ActorHasTag("SpaceShip"))
        if (IRechargeable* Rechargeable = Cast<IRechargeable>(Other))
            Rechargeable->Recharge();
}
