// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameStateBase.h"

void AMyGameStateBase::S_SendMessageToAll_Implementation(const FText& ToSend)
{
	//Multi_SendMessageToAll(ToSend);
}

bool AMyGameStateBase::S_SendMessageToAll_Validate(const FText& ToSend)
{
	return true;
}

void AMyGameStateBase::Multi_SendMessageToAll_Implementation(const FText&String)
{
	if (!HasAuthority())
	{
		OnSendingToAllMessageDelegate.Broadcast(String);
	}
	
}


void AMyGameStateBase::SendMessageToAll(const FText& ToSend)
{
	/*
	if (!HasAuthority())
	{

		S_SendMessageToAll(ToSend);
		return;
	}
	*/
	FString String = "Message";
	Multi_SendMessageToAll(ToSend);
}