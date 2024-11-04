// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHealthBar.h"
#include "Kismet/GameplayStatics.h"
#include "../UTAD_UI_FPSCharacter.h"
#include "Components/ProgressBar.h"
#include "Math/Color.h"
#include "Styling/SlateColor.h"

#define BLINK_ANIMATION_TIME 0.5f
#define BLINK_THRESHOLD 0.25f


void UPlayerHealthBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Update blinking effect if low health
	if (bIsLowHealth)
	{
		BlinkTimer += InDeltaTime;
		if (BlinkTimer >= BLINK_ANIMATION_TIME)
		{
			BlinkTimer = 0.0f;
			bBlinkTurningRed = !bBlinkTurningRed; // Toggle the state
		}

		
		LowHealthBlink();
	}

	
}

void UPlayerHealthBar::NativeConstruct()
{
	Super::NativeConstruct();

	if( AUTAD_UI_FPSCharacter * FPSCharacter = Cast<AUTAD_UI_FPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		FPSCharacter->OnHealthChanged.AddDynamic(this, &UPlayerHealthBar::UpdatePlayerHealthBar);
	}
}

void UPlayerHealthBar::NativeDestruct()
{
	Super::NativeDestruct();

	if( AUTAD_UI_FPSCharacter * FPSCharacter = Cast<AUTAD_UI_FPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		FPSCharacter->OnHealthChanged.RemoveDynamic(this, &UPlayerHealthBar::UpdatePlayerHealthBar);
	}
}

void UPlayerHealthBar::Show_Implementation()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UPlayerHealthBar::Hide_Implementation()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerHealthBar::UpdatePlayerHealthBar(int NewHealth, int MaxHealth)
{
	if (HealthProgressBar)
	{
		float HealthPercent = static_cast<float>(NewHealth) / static_cast<float>(MaxHealth);
		HealthProgressBar->SetPercent(HealthPercent);

		bIsLowHealth = HealthPercent < BLINK_THRESHOLD; // Start blinking if health is below BLINK_THRESHOLD
	}
}

void UPlayerHealthBar::LowHealthBlink()
{
	if (HealthProgressBar)
	{
		// Set the target color based on low health state
		TargetColor = bBlinkTurningRed ? FLinearColor::Red : FLinearColor::Black;

		// Interpolate between the current color and the target color
		CurrentColor = FMath::Lerp(CurrentColor, TargetColor, ColorChangeSpeed * GetWorld()->GetDeltaSeconds());

		// Set the BackgroundImage image tint color
		FProgressBarStyle ProgressBarStyle = HealthProgressBar->GetWidgetStyle();
		FSlateBrush BackgroundBrush = ProgressBarStyle.BackgroundImage;
		BackgroundBrush.TintColor = FSlateColor(CurrentColor);

		// Apply the modified fill image back to the style
		ProgressBarStyle.BackgroundImage = BackgroundBrush;
		HealthProgressBar->SetWidgetStyle(ProgressBarStyle);
	}
}