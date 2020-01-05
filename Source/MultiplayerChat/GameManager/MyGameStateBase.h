// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSendingToAllMessage, const FText&, ToSend);
/**
 * 
 */
UCLASS()
class MULTIPLAYERCHAT_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	FOnSendingToAllMessage OnSendingToAllMessageDelegate;
protected:

	UFUNCTION(Server, Reliable,WithValidation)
		void S_SendMessageToAll(const FText& ToSend);
	UFUNCTION(NetMulticast, Reliable)
		void Multi_SendMessageToAll(const FText&String);
public:
	void SendMessageToAll(const FText& ToSend);
};
