// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHitMarker.h"

#include "Kismet/GameplayStatics.h"
#include "UTAD_UI_FPS/UTAD_UI_FPSCharacter.h"

void UPlayerHitMarker::Show()
{
	// Set the hit marker to visible
	SetVisibility(ESlateVisibility::Visible);
	bIsHitMarkerVisible = true;

	// Hide after a delay
	GetWorld()->GetTimerManager().ClearTimer(HitMarkerTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(HitMarkerTimerHandle, this, &UPlayerHitMarker::Hide, HitMarkerDisplayDuration, false);
}

void UPlayerHitMarker::Hide()
{
	// Set the hit marker to hidden
	SetVisibility(ESlateVisibility::Hidden);
	bIsHitMarkerVisible = false;
}

void UPlayerHitMarker::OnTakeDamage()
{
	
	GetWorld()->GetTimerManager().ClearTimer(HitMarkerTimerHandle);
	Show();

}

void UPlayerHitMarker::NativeConstruct()
{
	
	Super::NativeConstruct();

	if( AUTAD_UI_FPSCharacter * FPSCharacter = Cast<AUTAD_UI_FPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		FPSCharacter->OnDamageReceive.AddDynamic(this, &UPlayerHitMarker::OnTakeDamage);
	}
}

void UPlayerHitMarker::NativeDestruct()
{
	Super::NativeDestruct();
	
	if( AUTAD_UI_FPSCharacter * FPSCharacter = Cast<AUTAD_UI_FPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		FPSCharacter->OnDamageReceive.AddDynamic(this, &UPlayerHitMarker::OnTakeDamage);
	}
}
