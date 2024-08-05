#pragma once

#include "CoreMinimal.h"
#include "HittableObject.h"
#include "Checkpoint.generated.h"

UCLASS()
class HITTABLEOBJECTS_API ACheckpoint : public AHittableObject
{
    GENERATED_BODY()

public:
    ACheckpoint();
};
