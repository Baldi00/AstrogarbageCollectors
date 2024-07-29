#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "SpaceShipRechargerComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLAYER_API USpaceShipRechargerComponent : public USphereComponent
{
	GENERATED_BODY()

public:	
	USpaceShipRechargerComponent();

    UFUNCTION()
    void OnOverlapActor(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
