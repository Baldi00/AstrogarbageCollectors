#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackHole.generated.h"

class UStaticMeshComponent;

UCLASS()
class SHOOTING_API ABlackHole : public AActor
{
    GENERATED_BODY()

    UPROPERTY(Category = BlackHole, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UStaticMeshComponent> Mesh;

    UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Replicated)
    AActor* HitActor;

    UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Replicated)
    FVector HitActorStartLocation;

public:
    ABlackHole();

    void SetHitActor(AActor* InHitActor);

    UFUNCTION(BlueprintCallable)
    void OnBlackHoleAnimationEnded();

protected:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
