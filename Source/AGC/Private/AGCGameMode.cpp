#include "AGCGameMode.h"
#include "AGCGameState.h"
#include "Kismet/GameplayStatics.h"
#include "HittableObject.h"

void AAGCGameMode::ResetGame()
{
    GetGameState<AAGCGameState>()->ResetState();

    // Destroy and recreate all hittable objects
    TArray<AActor*> HittableObjects;
    UGameplayStatics::GetAllActorsOfClass(this, AHittableObject::StaticClass(), HittableObjects);
    for (AActor* HittableObject : HittableObjects)
        HittableObject->Destroy();

    GetWorld()->SpawnActor<AActor>(HittableObjectsSpawnerClass);
}
