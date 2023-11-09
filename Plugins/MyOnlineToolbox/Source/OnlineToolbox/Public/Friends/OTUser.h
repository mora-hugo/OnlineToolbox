// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OTUser.generated.h"

USTRUCT(BlueprintType)
struct ONLINETOOLBOX_API FOTUser
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly,Category="User Informations")
	FString Name;
	
	TSharedPtr<FUniqueNetId const> UserId;


	
};
    