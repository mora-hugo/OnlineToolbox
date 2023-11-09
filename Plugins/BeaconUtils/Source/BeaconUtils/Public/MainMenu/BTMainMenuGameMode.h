// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/OnlineSession.h"
#include "BTMainMenuGameMode.generated.h"

/**
 * 
 */


UCLASS()
class BEACONUTILS_API ABTMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ABTMainMenuGameMode();


protected:
	UFUNCTION(BlueprintCallable)
	bool CreateHostBeacon();

	UFUNCTION(BlueprintCallable,BlueprintPure)
	class ABTBeaconHostObject* GetBeaconHost() const;
public:

protected:

	UPROPERTY()
	TObjectPtr<class ABTBeaconHostObject> HostObject;

	UPROPERTY()
	TObjectPtr<class AOnlineBeaconHost> Host;


	
};
