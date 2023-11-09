// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FLobbyInfo.h"
#include "OnlineBeaconHostObject.h"
#include "BTBeaconHostObject.generated.h"

/**
 *
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FServerOnLobbyInfoUpdated, const FLobbyInfo&, LobbyInfo);
UCLASS()
class BEACONUTILS_API ABTBeaconHostObject : public AOnlineBeaconHostObject
{
	GENERATED_BODY()

public:
	ABTBeaconHostObject();

	void SendLobbyInfo();
	
	UFUNCTION(BlueprintCallable)
	void DisconnectAllClients();

	UFUNCTION(BlueprintCallable)
	void ServerShutdown();
	
	virtual void DisconnectClient(AOnlineBeaconClient* ClientActor) override;

	
	
protected:
	virtual void OnClientConnected(AOnlineBeaconClient* NewClientActor, UNetConnection* ClientConnection) override;
	virtual void NotifyClientDisconnected(AOnlineBeaconClient* LeavingClientActor) override;
protected:
	UPROPERTY(BlueprintAssignable)
	FServerOnLobbyInfoUpdated ServerOnLobbyInfoUpdatedDelegate;
	
	FLobbyInfo LobbyInfo;
	
};
