#pragma once

#include "FLobbyInfo.generated.h"
USTRUCT(BlueprintType)
struct FLobbyInfo
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly)
	TArray<FString> Players;
	
	UPROPERTY(BlueprintReadOnly)
	FString LobbyName;
	
};
