#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "AGCGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSessionFound);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSessionNotFound);

UCLASS()
class AGC_API UAGCGameInstance : public UGameInstance
{
	GENERATED_BODY()

	FName SessionName;

public:
	UAGCGameInstance();

	UFUNCTION(BlueprintCallable)
	void Host(const int32 Players);

	UFUNCTION(BlueprintCallable)
	void Join();

	UPROPERTY(BlueprintAssignable)
	FOnSessionFound OnSessionFound;

	UPROPERTY(BlueprintAssignable)
	FOnSessionNotFound OnSessionNotFound;

	UPROPERTY(BlueprintReadWrite)
	FString PlayerName;

private:
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> LobbyMap;

	TSharedPtr<FOnlineSessionSearch> SearchSettings;

	FDelegateHandle CreateSessionCompleteDelegateHandle;
	FDelegateHandle JoinSessionCompleteDelegateHandle;
	FDelegateHandle FindSessionsCompleteDelegateHandle;

	void CreateAGCSession(const int32 Players);
	void OnCreateAGCSessionComplete(const FName Name, const bool bSucceeded);

	void FindAGCSession();
	void OnFindAGCSessionsComplete(const bool bSucceeded);
	
	void JoinAGCSession(const FOnlineSessionSearchResult& Session);
	void OnJoinAGCSessionComplete(const FName Name, const EOnJoinSessionCompleteResult::Type Result);

	void DestroyAGCSession();
};
