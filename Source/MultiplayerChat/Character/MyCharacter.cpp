// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "MultiplayerChat/GameManager/MyGameStateBase.h"
#include "MultiplayerChat/UI/MainChatBox.h"
// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
    MyChatBox=CreateWidget<UMainChatBox>(GetWorld(), MainChatBoxClass);
	if (MyChatBox)
	{
		//MyChatBox->OnSendingTextDelegate.BindUFunction(this, "OnSendText");
		MyChatBox->AddToViewport();
	}

	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//PlayerInputComponent->BindAction("CommitChat", IE_Pressed, this, &AMyCharacter::OnEnterPressed);
}

void AMyCharacter::OnSendText(const FText& TextSent)
{
	FString String = TextSent.ToString();

	UE_LOG(LogTemp, Warning, TEXT("OnSendText"));
	

		S_OnSendText(TextSent);
	
	
	/*
	if(!GetWorld()) { return; }
	auto GameState = GetWorld()->GetGameState();
	if (!GameState) { return; }
	auto MyGameState = Cast < AMyGameStateBase>(GameState);
	if (!MyGameState) { return; }
	MyGameState->SendMessageToAll(TextSent);
	*/
}


void AMyCharacter::S_OnSendText_Implementation(const FText& TextSent)
{
	UE_LOG(LogTemp, Warning, TEXT("S_OnSendText"));
	if (!GetWorld()) { return; }
	auto GameState = GetWorld()->GetGameState();
	if (!GameState) { return; }
	auto MyGameState = Cast < AMyGameStateBase>(GameState);
	if (!MyGameState) { return; }
	MyGameState->SendMessageToAll(TextSent);
}


bool AMyCharacter::S_OnSendText_Validate(const FText& TextSent)
{
	return true;
}