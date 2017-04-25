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

	void RequestTokenComplete(const FString& Token)
	{
		UE_LOG(LogClass, Warning, TEXT("Test"));
	}
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
		//class UWebConnection* WebConnect2;
		
	FTimerHandle ObjectCheckTimer;

	UFUNCTION()
		void CheckUObjectAlive();

	UPROPERTY()
		FStreamableManager AssetLoader;

	UFUNCTION() //�̰� ��� ���� �ʿ�� ����
		void RequestTokenComplete(const FString& Token);

	UFUNCTION() //�̰� ��� ���� �ʿ�� ����
		void RequestTokenComplete2(const FString& Token);
};