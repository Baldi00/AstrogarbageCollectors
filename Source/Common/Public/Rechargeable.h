#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Rechargeable.generated.h"

UINTERFACE(MinimalAPI)
class URechargeable : public UInterface
{
    GENERATED_BODY()
};

class COMMON_API IRechargeable
{
    GENERATED_BODY()

public:
    virtual void Recharge() = 0;
};
