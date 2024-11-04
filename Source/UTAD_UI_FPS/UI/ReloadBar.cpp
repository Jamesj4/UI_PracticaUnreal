// Fill out your copyright notice in the Description page of Project Settings.


#include "ReloadBar.h"
#include "../UTAD_UI_FPSCharacter.h"
#include "../TP_WeaponComponent.h"
#include "Components/ProgressBar.h"

void UReloadBar::Show_Implementation()
{
	SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UReloadBar::Hide_Implementation()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UReloadBar::UpdateReloadBarValue(float NewValue)
{

}
