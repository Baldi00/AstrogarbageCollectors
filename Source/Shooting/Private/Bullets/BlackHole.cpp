#include "Bullets/BlackHole.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"
#include "SpaceShipPlayerStateInterface.h"
#include "GameFramework/PlayerState.h"

ABlackHole::ABlackHole()
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

    static FName MeshCollisionProfileName(TEXT("NoCollision"));
    Mesh->SetCollisionProfileName(MeshCollisionProfileName);
    Mesh->SetNotifyRigidBodyCollision(false);
    Mesh->SetGenerateOverlapEvents(false);

    RootComponent = Mesh;

    bReplicates = true;
}

void ABlackHole::SetHitActor(AActor* InHitActor)
{
    HitActor = InHitActor;
    HitActorStartLocation = InHitActor->GetActorLocation();
}

void ABlackHole::OnBlackHoleAnimationEnded()
{
    if (HasAuthority())
    {
        if (IsValid(HitActor))
            HitActor->Destroy();

        if (APawn* OwnerPawn = Cast<APawn>(GetOwner()))
        {
            ISpaceShipPlayerStateInterface* PlayerState = Cast<ISpaceShipPlayerStateInterface>(OwnerPawn->GetPlayerState());

            if (!PlayerState)
                return;

            if (HitActor->ActorHasTag("Satellite"))
            {
                PlayerState->IncreaseSatellitesDestroyed();
                PlayerState->OnRep_SatellitesDestroyed();
            }
            else if (HitActor->ActorHasTag("Asteroid"))
            {
                PlayerState->IncreaseAsteroidsDestroyed();
                PlayerState->OnRep_AsteroidsDestroyed();
            }
        }

        Destroy();
    }
}

void ABlackHole::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME_CONDITION(ABlackHole, HitActor, COND_InitialOnly);
    DOREPLIFETIME_CONDITION(ABlackHole, HitActorStartLocation, COND_InitialOnly);
}
