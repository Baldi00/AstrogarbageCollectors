#include "SpaceShipRechargerComponent.h"
#include "Rechargeable.h"
#include "SpaceShip.h"
#include "SpaceShipMovementComponent.h"

USpaceShipRechargerComponent::USpaceShipRechargerComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USpaceShipRechargerComponent::BeginPlay()
{
    Super::BeginPlay();

    static FName OverlapAllProfile = TEXT("OverlapAll");
    static FName NoCollisionProfile = TEXT("NoCollision");

    if (APawn* Pawn = Cast<APawn>(GetOwner()); Pawn && Pawn->IsLocallyControlled())
    {
        SetCollisionProfileName(OverlapAllProfile);
        OnComponentBeginOverlap.AddUniqueDynamic(this, &USpaceShipRechargerComponent::OnOverlapActor);
    }
    else
        SetCollisionProfileName(NoCollisionProfile);
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
        ASpaceShip* OtherSpaceShip = Cast<ASpaceShip>(Other);
        if (!OtherSpaceShip)
            return;
        USpaceShipMovementComponent* OtherMovementComponent = OtherSpaceShip->GetSpaceShipMovementComponent();
        if (!OtherMovementComponent)
            return;
        if (OtherMovementComponent->GetCurrentFuelLevel() <= 0)
        {
            if (IRechargeable* Rechargeable = Cast<IRechargeable>(GetOwner()))
                Rechargeable->Recharge();
        }

        ASpaceShip* MySpaceShip = Cast<ASpaceShip>(GetOwner());
        if (!MySpaceShip)
            return;
        USpaceShipMovementComponent* MyMovementComponent = MySpaceShip->GetSpaceShipMovementComponent();
        if (!MyMovementComponent)
            return;
        if (MyMovementComponent->GetCurrentFuelLevel() <= 0)
        {
            if (IRechargeable* Rechargeable = Cast<IRechargeable>(GetOwner()))
                Rechargeable->Recharge();
        }
    }

}