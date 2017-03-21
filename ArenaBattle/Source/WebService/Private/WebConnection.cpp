// Fill out your copyright notice in the Description page of Project Settings.

#include "WebService.h"
#include "WebConnection.h"



UWebConnection::UWebConnection()
{
	UE_LOG(LogClass, Warning, TEXT("WebConnection Constructor!"));
	Host = TEXT("localhost:8000");
	URI = TEXT("/");
}

void UWebConnection::RequestToken()
{
	UE_LOG(LogClass, Warning, TEXT("Request Token Call!"));
}