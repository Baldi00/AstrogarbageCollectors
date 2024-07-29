#include "SpaceShipRechargerComponent.h"
#include "Rechargeable.h"
#include "SpaceShip.h"
#include "SpaceShipMovementComponent.h"

USpaceShipRechargerComponent::USpaceShipRechargerComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    static FName SphereColliderCollisionProfileName = TEXT("OverlapAll");
    SetCollisionProfileName(SphereColliderCollisionProfileName);
    OnComponentBeginOverlap.AddUniqueDynamic(this, &USpaceShipRechargerComponent::OnOverlapActor);
}

void USpaceShipRechargerComponent::OnOverlapActor(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (Other->ActorHasTag("Checkpoint"))
    {
        if (IRechargeable* Rechargeable = Cast<IRechargeable>(GetOwner()))
            Rechargeable->Recharge();
    }
    else if (Other->ActorHasTag("SpaceShip"))
    {
        ASpaceShip* SpaceShip = Cast<ASpaceShip>(Other);
        if (!SpaceShip)
            return;
        USpaceShipMovementComponent* MovementComponent = SpaceShip->GetSpaceShipMovementComponent();
        if (!MovementComponent)
            return;
        if (MovementComponent->GetCurrentFuelLevel() <= 0)
        {
            if (IRechargeable* Rechargeable = Cast<IRechargeable>(GetOwner()))
                Rechargeable->Recharge();
            if (IRechargeable* Rechargeable = Cast<IRechargeable>(Other))
                Rechargeable->Recharge();
        }
    }

}