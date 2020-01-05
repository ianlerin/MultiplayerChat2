// Fill out your copyright notice in the Description page of Project Settings.

#include "MainChatBox.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "D:/UnrealProjects/MultiplayerChat/Source/MultiplayerChat/Character/MyCharacter.h"
#include "Runtime/UMG/Public/Components/MultiLineEditableTextBox.h"
#include "Runtime/UMG/Public/Blueprint/WidgetTree.h"
#include "MultiplayerChat/GameManager/MyGameStateBase.h"
#include "Runtime/UMG/Public/Components/ScrollBox.h"
#include "MultiplayerChat/UI/SingleChatWidget.h"

void UMainChatBox::NativeConstruct()
{
	Super::NativeConstruct();
	auto Controller = UGameplayStatics::GetPlayerController(this, 0);
	if(!Controller) { return; }
	AMyCharacter* MyChar = Cast<AMyCharacter>(Controller->GetPawn());
	if (!MyChar) { return; }
	//MyChar->OnCommittingTextDelegate.BindUFunction(this, "AddChat");
	//InputBar->OnTextCommitted.AddDynamic(this, &UMainChatBox::AddChat);
	InputBar->OnTextChanged.AddDynamic(this, &UMainChatBox::OnTextChanged);
	auto GameState = GetWorld()->GetGameState();
	if (!GameState) { return; }
	auto MyGameState = Cast < AMyGameStateBase>(GameState);
	if (!MyGameState) { return; }
	MyGameState->OnSendingToAllMessageDelegate.AddDynamic(this, &UMainChatBox::AddChat);
	
}
void UMainChatBox::OnPlayerCommitText()
{
	//InputBar->OnTextCommitted.Broadcast(InputBar->GetText(), ETextCommit::OnEnter);
}

void UMainChatBox::OnTextChanged(const FText& Text)
{
	UE_LOG(LogTemp, Warning, TEXT("OnTextChanged:%s"), *Text.ToString());
}
void UMainChatBox::AddChat(const FText& ToAdd)
{
	SingleChat =CreateWidget<USingleChatWidget>(this, SingleWidgetClass);
	
	//auto SingleChat = WidgetTree->ConstructWidget<USingleChatWidget>(SingleWidgetClass, "Single Chat");
	if (SingleChat)
	{
		SingleChat->SetText(ToAdd);
		
		if (ShowBox)
		{
			UE_LOG(LogTemp, Warning, TEXT("AddChat"));
			ShowBox->AddChild(SingleChat);
			ShowBox->ScrollToEnd();
			
		}
		
	}

}

FReply UMainChatBox::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	UE_LOG(LogTemp, Warning, TEXT("NativeOnPreviewKeyDown"));
	if (!InKeyEvent.IsShiftDown()&&InKeyEvent.GetKey() == FKey("Enter"))
	{
		UE_LOG(LogTemp, Warning, TEXT("NativeOnPreviewKeyDown, enter"));
		//AddChat(InputBar->GetText());
		FText Text = InputBar->GetText();
		auto Controller = UGameplayStatics::GetPlayerController(this, 0);
		if (!Controller) { 

			UE_LOG(LogTemp, Warning, TEXT("NativeOnPreviewKeyDown, no controller"));
			return FReply::Handled();
		}
		AMyCharacter* MyChar = Cast<AMyCharacter>(Controller->GetPawn());
		if (!MyChar) {

			UE_LOG(LogTemp, Warning, TEXT("NativeOnPreviewKeyDown, no char"));
			return FReply::Handled();
		}
		MyChar->OnSendText(Text);
		//OnSendingTextDelegate.ExecuteIfBound(Text);
		InputBar->SetText(InputBar->HintText);
		
		return FReply::Handled();

	}

	return FReply::Unhandled();
}