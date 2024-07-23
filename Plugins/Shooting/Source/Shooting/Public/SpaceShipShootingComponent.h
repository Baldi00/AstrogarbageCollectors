#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SceneComponent.h"
#include "SpaceShipShootingComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTING_API USpaceShipShootingComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> LaserRayBulletClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> DestroyDecomposerBulletClass;

	USceneComponent* LeftLaserRaySceneComponent = nullptr;
	USceneComponent* RightLaserRaySceneComponent = nullptr;
	USceneComponent* CentralDestroyDecomposerSceneComponent = nullptr;

public:	
	USpaceShipShootingComponent();

	void SetShootingSceneComponents(USceneComponent* Left, USceneComponent* Center, USceneComponent* Right);
	void ShootLaserRays();
	void ShootDestroyDecomposer();
};
