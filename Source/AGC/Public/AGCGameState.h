#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AGCGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerStateAdded);

UCLASS()
class AGC_API AAGCGameState : public AGameStateBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, meta = (AllowPrivateAccess = "true"))
	float CurrentTimer = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float InitialTimer = 120;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "End Game", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> EndGameUIClass;

	UUserWidget* EndGameUI;

	UPROPERTY(Replicated, ReplicatedUsing = "OnRep_IsInEndGame")
	bool bIsInEndGame = false;

public:
	AAGCGameState();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetTimerString() const;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerStateAdded OnPlayerStateAdded;

	UFUNCTION(BlueprintCallable)
	void ResetState();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void AddPlayerState(APlayerState* NewPlayerState) override;

	UFUNCTION()
	void OnRep_IsInEndGame();
};
