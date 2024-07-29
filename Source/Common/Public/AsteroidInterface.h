#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AsteroidInterface.generated.h"

UINTERFACE(MinimalAPI)
class UAsteroidInterface : public UInterface
{
    GENERATED_BODY()
};

class COMMON_API IAsteroidInterface
{
    GENERATED_BODY()

public:
    virtual void DestroyAsteroid() = 0;
};
