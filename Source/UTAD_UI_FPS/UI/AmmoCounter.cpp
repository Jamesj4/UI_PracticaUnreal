// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoCounter.h"
#include "../UTAD_UI_FPSCharacter.h"
#include "../TP_WeaponComponent.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UAmmoCounter::Show_Implementation()
{
	SetVisibility(ESlateVisibility::HitTestInvisible);

	if( AUTAD_UI_FPSCharacter * FPSCharacter = Cast<AUTAD_UI_FPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		if(UTP_WeaponComponent* weapon = FPSCharacter->GetAttachedWeaponComponent())
		{
			weapon->OnAmmoChanged.AddDynamic(this ,&UAmmoCounter::UpdateCurrentAmmo);
		}
	}
}
void UAmmoCounter::Hide_Implementation()
{
	SetVisibility(ESlateVisibility::Hidden);

	if( AUTAD_UI_FPSCharacter * FPSCharacter = Cast<AUTAD_UI_FPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		if(UTP_WeaponComponent* weapon = FPSCharacter->GetAttachedWeaponComponent())
		{
			weapon->OnAmmoChanged.RemoveDynamic(this ,&UAmmoCounter::UpdateCurrentAmmo);
		}
	}
}

void UAmmoCounter::NativeConstruct()
{
	Super::NativeConstruct();

	if( AUTAD_UI_FPSCharacter * FPSCharacter = Cast<AUTAD_UI_FPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		FPSCharacter->OnAmmoCountChanged.AddDynamic(this, &UAmmoCounter::UpdateMaxCurrentAmmo);
	}
}

void UAmmoCounter::NativeDestruct()
{
	Super::NativeDestruct();

	if( AUTAD_UI_FPSCharacter * FPSCharacter = Cast<AUTAD_UI_FPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		FPSCharacter->OnAmmoCountChanged.AddDynamic(this, &UAmmoCounter::UpdateMaxCurrentAmmo);
	}
}



void UAmmoCounter::UpdateCurrentAmmo(int NewCurrentAmmo)
{
	// Update the UI Text to reflect the current ammo
	if (CurrentAmmoTextWidget)
	{
		CurrentAmmoTextWidget->SetText(FText::FromString(FString::Printf(TEXT("%d"), NewCurrentAmmo)));
	}
	

}


void UAmmoCounter::UpdateMaxCurrentAmmo(int NewTotalAmmo)
{
	// Update the UI Text to reflect the Max ammo
	if (MaxAmmoTextWidget)
	{
		MaxAmmoTextWidget->SetText(FText::FromString(FString::Printf(TEXT("%d"), NewTotalAmmo)));
	}
}

