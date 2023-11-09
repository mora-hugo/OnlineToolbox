// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FLobbyInfo.h"
#include "OnlineBeaconClient.h"
#include "Sessions/Structs/OTSessionSearchResult.h"
#include "BTBeaconClient.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConnectedResponseReceived, bool, bIsConnected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLobbyInfoUpdated, const FLobbyInfo&, LobbyInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDisconnected);

/**
 * 
 */
UCLASS()
class BEACONUTILS_API ABTBeaconClient : public AOnlineBeaconClient
{
	GENERATED_BODY()
public:
	ABTBeaconClient();

	UFUNCTION(Client, Reliable)
	virtual void Client_OnDisconnected();

	UFUNCTION(BlueprintCallable)
	void Connect2(const FOTSessionSearchResult& SessionResult);
	
	UFUNCTION(Client, Reliable)
	void Client_OnLobbyInfoUpdated(const FLobbyInfo& LobbyInfo);

protected:
	UFUNCTION(BlueprintCallable)
	bool ConnectToServer(const FString& Address);

	UFUNCTION(BlueprintCallable)
	void LeaveLobby();

	virtual void OnConnected() override;
	virtual void OnFailure() override;
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnConnectedResponseReceived OnConnectedResponseReceivedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnDisconnected OnDisconnectedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnLobbyInfoUpdated OnLobbyInfoUpdatedDelegate;

protected:
	FLobbyInfo LastLobbyInfo;
};
