// Fill out your copyright notice in the Description page of Project Settings.


#include "SplashWidget.h"

#include "Kismet/GameplayStatics.h"


void USplashWidget::Show_Implementation()
{
	SetVisibility(ESlateVisibility::Visible);

}

void USplashWidget::EnableSplashScreen(FWidgetAnimationDynamicEvent AnimationFinishedEvent)
{
	Show_Implementation();
	
	if (TransitionAnimation)
	{
		// Bind the animation finished event
		BindToAnimationFinished(TransitionAnimation, AnimationFinishedEvent);


		// Play the animation
		PlayAnimation(TransitionAnimation);
	}
}
void USplashWidget::Hide_Implementation()
{
	SetVisibility(ESlateVisibility::Hidden);

}



