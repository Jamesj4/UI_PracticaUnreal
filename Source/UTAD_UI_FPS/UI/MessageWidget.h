// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MessageWidget.generated.h"

/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UMessageWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable, Category = "Message")
	void ShowMessage(FString NewMessage,float DisplayTime);

	UFUNCTION(BlueprintCallable, Category = "Message")
	void HideMessage();

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MessageText;

	float RemainingDisplayTime = 0.0f;
	bool bIsMessageVisible = false;
};