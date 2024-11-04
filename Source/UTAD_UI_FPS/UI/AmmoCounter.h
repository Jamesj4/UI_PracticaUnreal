// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VisibilityInterface.h"
#include "Blueprint/UserWidget.h"
#include "AmmoCounter.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UAmmoCounter : public UUserWidget, public IVisibilityInterface
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable, Category = "Visibility")
	virtual void Show_Implementation() override;
	
	UFUNCTION(BlueprintCallable, Category = "Visibility")
	virtual void Hide_Implementation() override;

protected:

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentAmmoTextWidget;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxAmmoTextWidget;
	
	UFUNCTION()
	void UpdateCurrentAmmo(int NewCurrentAmmo);
	UFUNCTION()
	void UpdateMaxCurrentAmmo(int NewTotalAmmo);
};
