// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHealthBar.h"
#include "Components/ProgressBar.h"



void UEnemyHealthBar::Show_Implementation()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UEnemyHealthBar::Hide_Implementation()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UEnemyHealthBar::UpdateEnemyHealthBar(int NewHealth, int MaxHealth)
{
	if (HealthProgressBarWidget)
	{
		float HealthPercent = static_cast<float>(NewHealth) / static_cast<float>(MaxHealth);
		HealthProgressBarWidget->SetPercent(HealthPercent);

	}
}

void UEnemyHealthBar::NativeConstruct()
{
	Super::NativeConstruct();

	if(!HealthProgressBarWidget)
	{
		HealthProgressBarWidget = Cast<UProgressBar>(GetWidgetFromName(TEXT("HealthProgressBarWidget")));
	}
}

