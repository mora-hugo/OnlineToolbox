// Fill out your copyright notice in the Description page of Project Settings.


#include "Beacon/BTBeaconClient.h"

#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

ABTBeaconClient::ABTBeaconClient()
{
}

void ABTBeaconClient::Connect2(const FOTSessionSearchResult& SessionResult)
{
	IOnlineSubsystem * OnlineSubsystem = IOnlineSubsystem::Get();
	if(!OnlineSubsystem) return;

	IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
	if(!SessionInterface) return;
	FString ConnectInfo;
	if (SessionInterface->GetResolvedConnectString(SessionResult.Native, NAME_BeaconPort, ConnectInfo))
	{
		ConnectToServer(ConnectInfo);
	}
}

void ABTBeaconClient::Client_OnDisconnected_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("[Client] Client disconnected from host beacon"));
	OnDisconnectedDelegate.Broadcast();
}

void ABTBeaconClient::Client_OnLobbyInfoUpdated_Implementation(const FLobbyInfo& LobbyInfo)
{
	UE_LOG(LogTemp, Warning, TEXT("[Client] Client received lobby info from host beacon"));
	OnLobbyInfoUpdatedDelegate.Broadcast(LobbyInfo);
	LastLobbyInfo = LobbyInfo;
}

bool ABTBeaconClient::ConnectToServer(const FString& Address)
{
	FURL Destination(nullptr, *Address, ETravelType::TRAVEL_Absolute);
	Destination.Port = 7787;
	return InitClient(Destination);
}

void ABTBeaconClient::LeaveLobby()
{
	DestroyBeacon();
	
}

void ABTBeaconClient::OnConnected()
{
	Super::OnConnected();
	UE_LOG(LogTemp, Warning, TEXT("[Client] Client connected to host beacon"));
	OnConnectedResponseReceivedDelegate.Broadcast(true);
}

void ABTBeaconClient::OnFailure()
{
	Super::OnFailure();
	UE_LOG(LogTemp, Warning, TEXT("[Client] Client failed to connect to host beacon"));
	OnConnectedResponseReceivedDelegate.Broadcast(false);
}

