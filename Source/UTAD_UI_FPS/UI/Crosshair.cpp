// Fill out your copyright notice in the Description page of Project Settings.


#include "Crosshair.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "UTAD_UI_FPS/TP_WeaponComponent.h"
#include "UTAD_UI_FPS/UTAD_UI_FPSCharacter.h"

void UCrosshair::NativeConstruct()
{
	Super::NativeConstruct();
    
	if (CrosshairImageWidget)
	{
		CrosshairImageWidget->SetRenderScale(FVector2D(CurrentScale, CurrentScale));
	}
}

void UCrosshair::Show_Implementation()
{
	SetVisibility(ESlateVisibility::HitTestInvisible);

	if( AUTAD_UI_FPSCharacter * FPSCharacter = Cast<AUTAD_UI_FPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		if(UTP_WeaponComponent* weapon = FPSCharacter->GetAttachedWeaponComponent())
		{
			weapon->FOnShoot.AddDynamic(this ,&UCrosshair::OnShoot);
			weapon->ONDetectingEnemy.AddDynamic(this ,&UCrosshair::DetectEnemy);
		}
	}
}

void UCrosshair::Hide_Implementation()
{
	SetVisibility(ESlateVisibility::Hidden);

	if( AUTAD_UI_FPSCharacter * FPSCharacter = Cast<AUTAD_UI_FPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		if(UTP_WeaponComponent* weapon = FPSCharacter->GetAttachedWeaponComponent())
		{
			weapon->FOnShoot.RemoveDynamic(this ,&UCrosshair::OnShoot);
		}
	}
}

void UCrosshair::OnShoot()
{
	AnimateCrosshair(); 
}

void UCrosshair::SetCrosshairColor(FLinearColor NewColor)
{
	if (CrosshairImageWidget)
	{
		CrosshairImageWidget->SetColorAndOpacity(NewColor); // Change crosshair color
	}
}

void UCrosshair::DetectEnemy(bool bOnTarget)
{
	if(bOnTarget)
	{
		SetCrosshairColor(FLinearColor::Red);
	}
	else
	{
		SetCrosshairColor(FLinearColor::White);
	}
}

void UCrosshair::AnimateCrosshair()
{
	// Increase the scale by the defined increment
	CurrentScale += ShootAnimationScaleIncrement;
    
	if (CrosshairImageWidget)
	{
		CrosshairImageWidget->SetRenderScale(FVector2D(CurrentScale, CurrentScale)); // Set the new scale
	}

	// Reset the scale after the specified duration
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(ResetScaleTimer); // Clear any existing timers
		GetWorld()->GetTimerManager().SetTimer(ResetScaleTimer, this, &UCrosshair::ResetCrosshairScale, AnimationDuration, false);
	}
}

void UCrosshair::ResetCrosshairScale()
{
	CurrentScale = 1.0f;
	if (CrosshairImageWidget)
	{
		CrosshairImageWidget->SetRenderScale(FVector2D(CurrentScale, CurrentScale)); // Set the scale back to normal
	}
}