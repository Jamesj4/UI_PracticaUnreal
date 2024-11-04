// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VisibilityInterface.h"
#include "Blueprint/UserWidget.h"
#include "Crosshair.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UCrosshair : public UUserWidget ,public IVisibilityInterface
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Visibility")
	virtual void Show_Implementation() override;
	
	UFUNCTION(BlueprintCallable, Category = "Visibility")
	virtual void Hide_Implementation() override;
	
	UFUNCTION(BlueprintCallable, Category = "Crosshair")
	void OnShoot(); // Function to call when the player shoots

	UFUNCTION()
	void SetCrosshairColor(FLinearColor NewColor); // Function to set crosshair color


	UFUNCTION()
	void DetectEnemy(bool bOnTarget);

protected:
	virtual void NativeConstruct() override;

private:
	
	UPROPERTY(meta = (BindWidget)) 
	UImage* CrosshairImageWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Crosshair")
	float ShootAnimationScaleIncrement = 0.2f; 

	UPROPERTY(EditDefaultsOnly, Category = "Crosshair")
	float AnimationDuration = 0.3f; 

	float CurrentScale = 1.0f; 
	FTimerHandle ResetScaleTimer; // Timer handle for resetting scale

	void AnimateCrosshair(); // Function to animate the crosshair
	void ResetCrosshairScale();
};