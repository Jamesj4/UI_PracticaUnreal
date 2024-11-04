// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VisibilityInterface.h"
#include "Blueprint/UserWidget.h"
#include "ReloadBar.generated.h"

/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UReloadBar : public UUserWidget ,public IVisibilityInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Visibility")
	virtual void Show_Implementation() override;
	
	UFUNCTION(BlueprintCallable, Category = "Visibility")
	virtual void Hide_Implementation() override;
private:

	void UpdateReloadBarValue(float NewValue);
};
