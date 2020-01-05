// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainChatBox.generated.h"

DECLARE_DELEGATE_OneParam(FOnSendingText,FText);
/**
 * 
 */
class UMultiLineEditableTextBox;
class UScrollBox;
class USingleChatWidget;
UCLASS()
class MULTIPLAYERCHAT_API UMainChatBox : public UUserWidget
{
	GENERATED_BODY()
protected:
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UMultiLineEditableTextBox* InputBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UScrollBox* ShowBox;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf < USingleChatWidget> SingleWidgetClass;
	UPROPERTY()
		USingleChatWidget* SingleChat = nullptr;
	void OnKeyDown(FGeometry MyGeometry, FKeyEvent InKeyEvent);
public:
	FOnSendingText OnSendingTextDelegate;
protected:
	void NativeConstruct()override;
	
	UFUNCTION()
		void OnTextChanged(const FText& Text);
	UFUNCTION()
		void OnPlayerCommitText();

	UFUNCTION(BlueprintImplementableEvent)
		void BPAddChat();
	FReply NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	UFUNCTION()
	void AddChat(const FText& ToAdd);
};
