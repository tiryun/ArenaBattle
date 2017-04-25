// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "WebConnection.generated.h"

//DECLARE_DELEGATE_OneParam(FTokenCompleteSignature, const FString&);
DECLARE_MULTICAST_DELEGATE_OneParam(FTokenCompleteSignature, const FString&);

/**
 * 
 */
UCLASS()
class WEBSERVICE_API UWebConnection : public UObject
{
	GENERATED_BODY()

public:
	UWebConnection();

	UPROPERTY()
		FString Host;

	UPROPERTY()
		FString URI;

	UFUNCTION()
		void RequestToken(const FString& UserID);

	FTokenCompleteSignature TokenCompleteDelegate;
};