// Fill out your copyright notice in the Description page of Project Settings.

#include "SingleChatWidget.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"

void USingleChatWidget::SetText(FText ToSet)
{
	SingleText->SetText(ToSet);
}
FText USingleChatWidget::GetText()
{
	return SingleText->Text;
}