#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class SHOOTING_API ABullet : public AActor
{
	GENERATED_BODY()

	UPROPERTY(Category = Bullet, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> DefaultSceneRoot;

	UPROPERTY(Category = Bullet, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(Category = Bullet, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float LifeTime = 2;

	UPROPERTY(Category = Bullet, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float Speed = 20000;
	
protected:
	// Cache
	FVector NextLocation;
	FHitResult HitResult;
	FCollisionQueryParams LineTraceQueryParams;

public:	
	ABullet();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void AddCollisionIgnoredActor(AActor* InIgnoredActor);

protected:
	void StepForward(float DeltaTime);
	void CheckCollisionsBetweenPreviousAndNextLocations();
	virtual void OnCollisionHappened();
};
