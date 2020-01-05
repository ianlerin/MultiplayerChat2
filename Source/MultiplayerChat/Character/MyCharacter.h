// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Static/MyDelegate.h"
#include "MultiplayerChatCharacter.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class UMainChatBox;

DECLARE_DELEGATE(FOnCommittingText);
UCLASS()
class MULTIPLAYERCHAT_API AMyCharacter : public AMultiplayerChatCharacter
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMainChatBox> MainChatBoxClass;
	UMainChatBox* MyChatBox;
public:
	FOnCommittingText OnCommittingTextDelegate;

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	


	UFUNCTION(Server, Reliable, WithValidation)
		void S_OnSendText(const FText& TextSent);
public:	

	UFUNCTION()
		void OnSendText(const FText& TextSent);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
