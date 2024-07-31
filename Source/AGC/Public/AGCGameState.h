#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AGCGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimerEnded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerStateAdded);

UCLASS()
class AGC_API AAGCGameState : public AGameStateBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, meta = (AllowPrivateAccess = "true"))
	float CurrentTimer = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float InitialTimer = 120;

public:
	AAGCGameState();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetTimerString() const;

	UPROPERTY(BlueprintAssignable)
	FOnTimerEnded OnTimerEnded;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerStateAdded OnPlayerStateAdded;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void AddPlayerState(APlayerState* NewPlayerState) override;
};
