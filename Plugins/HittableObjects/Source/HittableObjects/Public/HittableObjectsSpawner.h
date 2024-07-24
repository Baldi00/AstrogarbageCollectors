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
	int32 MinObjectsToSpawn = 100;

	UPROPERTY(Category = HittableObjectSpawner, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 MaxObjectsToSpawn = 300;

	UPROPERTY(Category = HittableObjectSpawner, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MaxSpawnRadius = 300000;

	UPROPERTY(Category = HittableObjectSpawner, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MinSpawnRadius = 1000;

	UPROPERTY(Category = HittableObjectSpawner, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float AsteroidSpawnProbability = 0.6f;

	UPROPERTY(Category = HittableObjectSpawner, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float SatelliteSpawnProbability = 0.2f;

	UPROPERTY(Category = HittableObjectSpawner, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float CheckpointSpawnProbability = 0.2f;

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
