#pragma once

#include "CoreMinimal.h"
#include "HittableObject.h"
#include "Checkpoint.generated.h"

class USphereComponent;

UCLASS()
class HITTABLEOBJECTS_API ACheckpoint : public AHittableObject
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Checkpoint", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USphereComponent> SphereCollider;

public:
    ACheckpoint();
};
