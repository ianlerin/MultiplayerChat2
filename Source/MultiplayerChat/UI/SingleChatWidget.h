// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SingleChatWidget.generated.h"

/**
 * 
 */
class UTextBlock;
UCLASS()
class MULTIPLAYERCHAT_API USingleChatWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
		UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* SingleText;
public: 

	FText GetText();
	UFUNCTION(BlueprintCallable)
	void SetText(FText ToSet);

};
