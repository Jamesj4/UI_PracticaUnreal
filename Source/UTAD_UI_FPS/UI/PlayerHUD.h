// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

class UAmmoCounter;
class UCrosshair;
class UPlayerHealthBar;
class UReloadBar;
class UPlayerHitMarker;
class USplashWidget;

/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:

	/** Show the Minimap and the PlayerHealthBar */
	UFUNCTION(BlueprintCallable, Category = Visibility)
	void ShowNoWeapon();

	/** Show all the widgets */
	UFUNCTION(BlueprintCallable, Category = Visibility)
	void ShowAll();

	/** Hide all the widgets */
	UFUNCTION(BlueprintCallable, Category = Visibility)
	void HideAll();


protected:
	virtual void NativeConstruct() override;
private:
	/** References to various HUD components */
	
	UPROPERTY(meta = (BindWidget))
	UAmmoCounter* AmmoCounterWidget;

	UPROPERTY(meta = (BindWidget))
	UCrosshair* CrosshairWidget;

	UPROPERTY(meta = (BindWidget))
	UPlayerHealthBar* PlayerHealthBarWidget;

	UPROPERTY(meta = (BindWidget))
	UReloadBar* ReloadBarWidget;


	UPROPERTY(meta = (BindWidget))
	UPlayerHitMarker* PlayerHitMarkerWidget;

	
	/******************************************/

	/** Array to store all HUD components for easy looping */
	UPROPERTY()
	TArray<UUserWidget*> HUDComponents;
};
