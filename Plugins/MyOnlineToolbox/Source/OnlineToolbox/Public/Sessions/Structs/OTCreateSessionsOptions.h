// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "OTCreateSessionsOptions.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct ONLINETOOLBOX_API FOTCreateSessionsOptions
{
 GENERATED_BODY()
 
 UPROPERTY(BlueprintReadWrite)
 bool bIsInLAN;
 
 UPROPERTY(BlueprintReadWrite)
 FString SessionName;
 
 UPROPERTY(BlueprintReadWrite)
 FString HostName;
 
 UPROPERTY(BlueprintReadWrite)
 FString Map;
 
 UPROPERTY(BlueprintReadWrite)
 FString SessionType;
 
 UPROPERTY(BlueprintReadWrite)
 int NumPublicConnections;

 

 
};
