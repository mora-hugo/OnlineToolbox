// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu/BTMainMenuGameMode.h"
#include "OnlineBeaconHost.h"
#include "Beacon/BTBeaconHostObject.h"

ABTMainMenuGameMode::ABTMainMenuGameMode() : HostObject{nullptr}, Host{nullptr}
{
	
}

bool ABTMainMenuGameMode::CreateHostBeacon()
{
	if((Host = GetWorld()->SpawnActor<AOnlineBeaconHost>(AOnlineBeaconHost::StaticClass())))
         	{
         		if(Host->InitHost())
         		{
         			Host->PauseBeaconRequests(false);
         			if((HostObject = GetWorld()->SpawnActor<ABTBeaconHostObject>(ABTBeaconHostObject::StaticClass())))
         			{
         				UE_LOG(LogTemp, Warning, TEXT("[Server] Host Beacon successfully created"));
         				Host->RegisterHost(HostObject);
         				return true;
         			}
         			else
         			{
         				UE_LOG(LogTemp, Warning, TEXT("Failed to spawn BeaconHostObject"));
         			}
         		}
		return true;
	}
	return false;
}

ABTBeaconHostObject* ABTMainMenuGameMode::GetBeaconHost() const
{
	return HostObject ? HostObject : nullptr;
}
