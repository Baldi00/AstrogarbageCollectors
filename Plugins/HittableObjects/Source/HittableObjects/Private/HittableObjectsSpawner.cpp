#include "HittableObjectsSpawner.h"
#include "Kismet/KismetMathLibrary.h"

AHittableObjectsSpawner::AHittableObjectsSpawner()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AHittableObjectsSpawner::BeginPlay()
{
    Super::BeginPlay();
    if (HasAuthority())
    {
        int32 ActorsToSpawn = UKismetMathLibrary::RandomIntegerInRange(MinObjectsToSpawn, MaxObjectsToSpawn);
        for (int i = 0; i < ActorsToSpawn; i++)
        {
            FVector SpawnLocation = UKismetMathLibrary::RandomUnitVector() * UKismetMathLibrary::RandomFloatInRange(MinSpawnRadius, MaxSpawnRadius);

            float SpawnProbability = UKismetMathLibrary::RandomFloatInRange(0, AsteroidSpawnProbability + SatelliteSpawnProbability + CheckpointSpawnProbability);

            if(SpawnProbability < AsteroidSpawnProbability)
                GetWorld()->SpawnActor<AHittableObject>(AsteroidClass, SpawnLocation, UKismetMathLibrary::RandomRotator());
            else if(SpawnProbability < AsteroidSpawnProbability + SatelliteSpawnProbability)
                GetWorld()->SpawnActor<AHittableObject>(SatelliteClass, SpawnLocation, UKismetMathLibrary::RandomRotator());
            else
                GetWorld()->SpawnActor<AHittableObject>(CheckpointClass, SpawnLocation, UKismetMathLibrary::RandomRotator());
        }
    }
    Destroy();
}