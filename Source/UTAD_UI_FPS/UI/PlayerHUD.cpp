// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "Crosshair.h"
#include "AmmoCounter.h"
#include "PlayerHealthBar.h"
#include "PlayerHitMarker.h"
#include "ReloadBar.h"
#include "SplashWidget.h"


void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

	// Add all HUD components to the HUDComponents array
	if (AmmoCounterWidget)
	{
		HUDComponents.Add(AmmoCounterWidget);
	}
	if (CrosshairWidget)
	{
		HUDComponents.Add(CrosshairWidget);
	}
	if (PlayerHealthBarWidget)
	{
		HUDComponents.Add(PlayerHealthBarWidget);
	}
	if (ReloadBarWidget)
	{
		HUDComponents.Add(ReloadBarWidget);
	}


	if(PlayerHitMarkerWidget) PlayerHitMarkerWidget->Hide();


}


void UPlayerHUD::ShowNoWeapon()
{

	// Hide other widgets specific to weapon HUD
	if (AmmoCounterWidget)
	{
		IVisibilityInterface::Execute_Hide(AmmoCounterWidget);
	}
	if (CrosshairWidget)
	{
		IVisibilityInterface::Execute_Hide(CrosshairWidget);
	}
	if (ReloadBarWidget)
	{
		IVisibilityInterface::Execute_Hide(ReloadBarWidget);
	}
}

void UPlayerHUD::ShowAll()
{
	for (UUserWidget* Component : HUDComponents)
	{
	
		IVisibilityInterface::Execute_Show(Component);
	}
}

void UPlayerHUD::HideAll()
{
	for (UUserWidget* Component : HUDComponents)
	{
		IVisibilityInterface::Execute_Hide(Component);
	}
}



