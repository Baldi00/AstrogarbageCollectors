#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HittableObjectsSpawner.h"
#include "AGCGameMode.generated.h"

UCLASS()
class AGC_API AAGCGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHittableObjectsSpawner> HittableObjectsSpawnerClass;

public:
	UFUNCTION()
	void ResetGame();
};
