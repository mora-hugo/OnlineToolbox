// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Sessions/OTJoinSessionResultType.h"
#include "Sessions/Structs/OTSessionSearchResult.h"


#include "Blueprint/UserWidget.h"
#include "OTSessionMenu.generated.h"

class UOTSessionsSubsystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSessionMenuCreationComplete, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSessionMenuSearchComplete, bool, bWasSuccessful, const TArray<FOTSessionSearchResult>&, SessionResults);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSessionMenuJoinComplete, bool, bWasSuccessful, EOTJoinSessionResultType, Type);

UCLASS()
class ONLINETOOLBOX_API UOTSessionMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void MenuSetup(bool AddWidgetToWiewport, bool RemoveAtTeardown);

protected:
	UFUNCTION(BlueprintCallable)
	void HostSession(const TSoftObjectPtr<UWorld> LobbyLevel, const FString& SessionName, int32 NumPublicConnection, const bool bIsLan, const FString& Map, const FString& SessionType);

	UFUNCTION(BlueprintCallable)
	void FindSession(bool bIsLan = false, const FString& SessionName = "", const FString& Map = "", const FString& SessionType = "", const int32 MaxSearchResults = 10);
	
	UFUNCTION(BlueprintCallable)
	void JoinSession(const FOTSessionSearchResult& session);


	virtual void NativeDestruct() override;
	
	// Callbacks for the toolbox session subsystem
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);

	UFUNCTION()
	void OnFindSession(const TArray<FOTSessionSearchResult>& SessionResults, bool bWasSuccessful);

	UFUNCTION()
	void OnJoinSession(bool bWasSuccessful, EOTJoinSessionResultType Type, const FString& Address);


	// Delegate for BP interaction
	UPROPERTY(BlueprintAssignable)
	FSessionMenuCreationComplete OnSessionCreateComplete;

	UPROPERTY(BlueprintAssignable)
	FSessionMenuSearchComplete OnSessionSearchComplete;

	UPROPERTY(BlueprintAssignable)
	FSessionMenuJoinComplete OnSessionJoinedComplete;
	
private:
	bool bRemoveAtTearDown;
	
	UPROPERTY()
	UOTSessionsSubsystem* OTSessionsSubsystem;

	void MenuTearDown();

	FString LobbyMap;
};
