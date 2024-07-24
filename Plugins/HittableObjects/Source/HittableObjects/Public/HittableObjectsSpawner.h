#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HittableObjectsSpawner.generated.h"

class AHittableObject;

UCLASS()
class HITTABLEOBJECTS_API AHittableObjectsSpawner : public AActor
{
	GENERATED_BODY()

	UPROPERTY(Category = HittableObjectSpawner, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 MaxObjectsToSpawn = 700;

	UPROPERTY(Category = HittableObjectSpawner, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MaxSpawnRadius = 150000;

	UPROPERTY(Category = HittableObjectSpawner, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MinSpawnRadius = 10000;

	UPROPERTY(Category = HittableObjectSpawner, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float AsteroidSpawnProbability = 0.4f;

	UPROPERTY(Category = HittableObjectSpawner, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float SatelliteSpawnProbability = 0.35f;

	UPROPERTY(Category = HittableObjectSpawner, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float CheckpointSpawnProbability = 0.25f;

	UPROPERTY(Category = HittableObjectSpawner, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AHittableObject> AsteroidClass;

	UPROPERTY(Category = HittableObjectSpawner, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AHittableObject> SatelliteClass;

	UPROPERTY(Category = HittableObjectSpawner, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AHittableObject> CheckpointClass;

public:	
	AHittableObjectsSpawner();
	
protected:
	virtual void BeginPlay() override;
};
