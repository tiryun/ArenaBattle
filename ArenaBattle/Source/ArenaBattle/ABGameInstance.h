// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "WebConnection.h" 
#include "ABGameInstance.generated.h"


class FHouse
{
public:
	TSharedPtr<FHouse> OthersDeed;
	TWeakPtr<FHouse> AccessHouse;
	int32 Size = 10;
};
/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UABGameInstance();

	virtual void Init() override;

	UPROPERTY()
		class UWebConnection* WebConnect;

	//UPROPERTY()
		class UWebConnection* WebConnect2;
		
	FTimerHandle ObjectCheckTimer;

	UFUNCTION()
		void CheckUObjectAlive();

	UPROPERTY()
		FStreamableManager AssetLoader;
};