// Fill out your copyright notice in the Description page of Project Settings.


#include "MessageWidget.h"

#include "Components/TextBlock.h"


void UMessageWidget::ShowMessage(FString NewMessage,float DisplayTime)
{
	if (MessageText)
	{
		MessageText->SetText(FText::FromString(NewMessage));
	}

	SetVisibility(ESlateVisibility::Visible);
	RemainingDisplayTime = DisplayTime; // Set the countdown time
	bIsMessageVisible = true; 
	
}

void UMessageWidget::HideMessage()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UMessageWidget::NativeConstruct()
{
	Super::NativeConstruct();

	
	SetVisibility(ESlateVisibility::Hidden);
}

void UMessageWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bIsMessageVisible && RemainingDisplayTime > 0.0f)
	{
		RemainingDisplayTime -= InDeltaTime;

		if (RemainingDisplayTime <= 0.0f)
		{
			SetVisibility(ESlateVisibility::Hidden); // Hide the widget
			bIsMessageVisible = false; // Reset the visibility flag
		}
	}
}
