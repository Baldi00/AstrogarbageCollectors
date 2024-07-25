#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HittableObject.generated.h"

UCLASS()
class HITTABLEOBJECTS_API AHittableObject : public AActor
{
	GENERATED_BODY()

	UPROPERTY(Category = HittableObject, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(Replicated)
	FVector Velocity = FVector::ZeroVector;
	UPROPERTY(Replicated)
	FRotator AngularVelocity = FRotator::ZeroRotator;

	UPROPERTY(ReplicatedUsing = "OnRep_CurrentLocation")
	FVector CurrentLocation = FVector::ZeroVector;
	UPROPERTY(ReplicatedUsing = "OnRep_CurrentRotation")
	FRotator CurrentRotation = FRotator::ZeroRotator;

public:	
	AHittableObject();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_CurrentLocation();
	UFUNCTION()
	void OnRep_CurrentRotation();
};
