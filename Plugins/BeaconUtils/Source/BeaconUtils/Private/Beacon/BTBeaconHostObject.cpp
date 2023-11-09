// Fill out your copyright notice in the Description page of Project Settings.


#include "Beacon/BTBeaconHostObject.h"

#include "OnlineBeaconHost.h"
#include "Beacon/BTBeaconClient.h"
#include "MainMenu/BTMainMenuGameMode.h"

ABTBeaconHostObject::ABTBeaconHostObject()
{
	ClientBeaconActorClass = ABTBeaconClient::StaticClass();
	BeaconTypeName = ClientBeaconActorClass->GetName();
	LobbyInfo.Players.Add(FString("Player " + FString::FromInt(LobbyInfo.Players.Num()) + " (Host)" ));
	UE_LOG(LogTemp, Warning, TEXT("[Server] BeaconHostObject created : : %s"), *BeaconTypeName);
}

void ABTBeaconHostObject::SendLobbyInfo()
{
	UE_LOG(LogTemp, Warning, TEXT("[Server] Sending lobby info to all clients"));
	ServerOnLobbyInfoUpdatedDelegate.Broadcast(LobbyInfo);
	for(auto Client : ClientActors)
	{
		if(Client)
		{
			if(ABTBeaconClient * ClientActor = StaticCast<ABTBeaconClient*>(Client))
			{
				ClientActor->Client_OnLobbyInfoUpdated(LobbyInfo);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("[Server] Failed to cast in SendLobbyInfo method"  ));
			}
		}
	}
}

void ABTBeaconHostObject::DisconnectAllClients()
{
	UE_LOG(LogTemp, Warning, TEXT("[Server] Disconnecting all clients"));

	for(auto Client : ClientActors)
	{
		if(Client)
			DisconnectClient(Client);
	}
	
	
	//Unregister();

}

void ABTBeaconHostObject::ServerShutdown()
{
	DisconnectAllClients();
	
	if(AOnlineBeaconHost * Host = Cast<AOnlineBeaconHost>(GetOwner()))
	{
		UE_LOG(LogTemp, Warning, TEXT("[Server] Server has been shutting down ... Destroying the Host Beacon"));
		Host->UnregisterHost(BeaconTypeName);
		Host->DestroyBeacon();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[Server] Failed to cast in ServerShutdown method"  ));
	}
}

void ABTBeaconHostObject::DisconnectClient(AOnlineBeaconClient* ClientActor)
{
	AOnlineBeaconHost * BeaconHost = Cast<AOnlineBeaconHost>(GetOwner());
	if(BeaconHost)
	{
		if(ABTBeaconClient * Client = StaticCast<ABTBeaconClient*>(ClientActor))
		{
			UE_LOG(LogTemp, Warning, TEXT("[Server] Currently disconnecting : %s"  ), *Client->GetName());
			Client->Client_OnDisconnected();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("[Server] Failed to cast in DisconnectClient method"  ));
		}
		BeaconHost->DisconnectClient(ClientActor);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[Server] Failed to cast in DisconnectClient method"  ));
	}
	//Super::DisconnectClient(ClientActor);

}

void ABTBeaconHostObject::OnClientConnected(AOnlineBeaconClient* NewClientActor, UNetConnection* ClientConnection)
{
	Super::OnClientConnected(NewClientActor, ClientConnection);

	if(NewClientActor)
	{
		LobbyInfo.Players.Add(FString("Player " + FString::FromInt(LobbyInfo.Players.Num())));
		SendLobbyInfo();
		
		UE_LOG(LogTemp, Warning, TEXT("[Server] Client connected"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[Server] Client failed to connect"));
	}
}

void ABTBeaconHostObject::NotifyClientDisconnected(AOnlineBeaconClient* LeavingClientActor)
{
	Super::NotifyClientDisconnected(LeavingClientActor);
	if(ABTBeaconClient * Client = StaticCast<ABTBeaconClient*>(LeavingClientActor))
	{
		Client->Client_OnDisconnected();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[Server] Failed to cast in NotifyClientDisconnected method"  ));
	}

	UE_LOG(LogTemp, Warning, TEXT("[Server] Client disconnected : %s"), *LeavingClientActor->GetName());
	
	
}



