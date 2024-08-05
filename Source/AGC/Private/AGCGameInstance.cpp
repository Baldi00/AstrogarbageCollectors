#include "AGCGameInstance.h"
#include "OnlineSubsystemUtils.h"
#include "FindSessionsCallbackProxy.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameUserSettings.h"
#include "ABDebug.h"

UAGCGameInstance::UAGCGameInstance()
{
    SessionName = FPlatformProcess::ComputerName();
}

void UAGCGameInstance::Init()
{
    Super::Init();

    // Set vsync on
    UGameUserSettings* Settings = UGameUserSettings::GetGameUserSettings();
    Settings->SetVSyncEnabled(true);
    Settings->ApplySettings(true);
}

void UAGCGameInstance::Host(const int32 Players)
{
    if (Players < 2 || Players > 4)
        return;

    CreateAGCSession(Players);
}

void UAGCGameInstance::Join()
{
    FindAGCSession();
}

void UAGCGameInstance::CreateAGCSession(const int32 Players)
{
    IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld());

    CreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(
        FOnCreateSessionCompleteDelegate::CreateUObject(this, &UAGCGameInstance::OnCreateAGCSessionComplete));

    FOnlineSessionSettings SessionSettings{};
    SessionSettings.bIsLANMatch = true;
    SessionSettings.bShouldAdvertise = true;
    SessionSettings.NumPublicConnections = Players;
    SessionInterface->CreateSession(0, SessionName, SessionSettings);
}

void UAGCGameInstance::OnCreateAGCSessionComplete(const FName Name, const bool bSucceeded)
{
    IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld());

    SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);

    if (!bSucceeded)
    {
        LOGF("Failed to create session '%s'.", *Name.ToString());
        DestroyAGCSession();
        return;
    }

    const FOnlineSessionSettings* SessionSettings{ SessionInterface->GetSessionSettings(SessionName) };
    if (!SessionSettings)
    {
        LOGF("Failed to find FOnlineSessionSettings for session '%s'", *Name.ToString());
        DestroyAGCSession();
        return;
    }

    // We can pass Options to the next GameMode.
    const FString ListenOption{ TEXT("?Listen") };
    const FString MaxPlayersOption{ FString::Printf(TEXT("?MaxPlayers=%i"), SessionSettings->NumPublicConnections) };
    const FString Options{ FString::Printf(TEXT("%s%s"), *ListenOption, *MaxPlayersOption) };
    UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), LobbyMap, true, Options);
}

void UAGCGameInstance::FindAGCSession()
{
    IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld());

    FindSessionsCompleteDelegateHandle = SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(
        FOnFindSessionsCompleteDelegate::CreateUObject(this, &UAGCGameInstance::OnFindAGCSessionsComplete));

    SearchSettings.Reset();
    SearchSettings = MakeShared<FOnlineSessionSearch>();
    SearchSettings->bIsLanQuery = true;
    SearchSettings->MaxSearchResults = 1;
    SessionInterface->FindSessions(0, SearchSettings.ToSharedRef());
}

void UAGCGameInstance::OnFindAGCSessionsComplete(const bool bSucceeded)
{
    IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld());

    SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegateHandle);

    const TArray<FOnlineSessionSearchResult>& SearchResults{ SearchSettings->SearchResults };
    if (!bSucceeded || SearchResults.Num() == 0)
    {
        OnSessionNotFound.Broadcast();
        LOG("Failed to find sessions.");
        return;
    }

    OnSessionFound.Broadcast();
    JoinAGCSession(SearchResults[0]);
}

void UAGCGameInstance::JoinAGCSession(const FOnlineSessionSearchResult& Session)
{
    IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld());

    JoinSessionCompleteDelegateHandle = SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(
        FOnJoinSessionCompleteDelegate::CreateUObject(this, &UAGCGameInstance::OnJoinAGCSessionComplete));

    SessionInterface->JoinSession(0, SessionName, Session);
}

void UAGCGameInstance::OnJoinAGCSessionComplete(const FName Name, const EOnJoinSessionCompleteResult::Type Result)
{
    IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld());

    SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegateHandle);

    if (Result != EOnJoinSessionCompleteResult::Success)
    {
        LOGF("Failed to join session %s", *Name.ToString());
        DestroyAGCSession();
        return;
    }

    APlayerController* PlayerController{ GetFirstLocalPlayerController(GetWorld()) };
    if (!IsValid(PlayerController))
    {
        LOG("PlayerController is invalid.");
        DestroyAGCSession();
        return;
    }

    FString JoinAddress{};
    if (!SessionInterface->GetResolvedConnectString(Name, JoinAddress) || JoinAddress.IsEmpty())
    {
        LOG("JoinAddress is empty.");
        DestroyAGCSession();
        return;
    }

    PlayerController->ClientTravel(JoinAddress, TRAVEL_Absolute);
}

void UAGCGameInstance::DestroyAGCSession()
{
    IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld());
    if (SessionInterface->GetNamedSession(SessionName) == nullptr)
    {
        LOGF("Session '%s' does not exist.", *SessionName.ToString());
        return;
    }

    FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate{};
    OnDestroySessionCompleteDelegate.BindWeakLambda(this, [this](const FName Name, const bool bSucceeded) -> void
        {
            if (!bSucceeded)
            {
                LOGF("Failed to destroy session '%s'.", *Name.ToString());
                return;
            }

            LOGF("Session '%s' destroyed succesfully.", *Name.ToString());
        });
    SessionInterface->DestroySession(SessionName, OnDestroySessionCompleteDelegate);
}