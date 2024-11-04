// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VisibilityInterface.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHealthBar.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UPlayerHealthBar : public UUserWidget,  public IVisibilityInterface
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Visibility")
	virtual void Show_Implementation() override;
	
	UFUNCTION(BlueprintCallable, Category = "Visibility")
	virtual void Hide_Implementation() override;
	UFUNCTION()
	void UpdatePlayerHealthBar(int NewHealth, int MaxHealth);

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
private:

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthProgressBar;
	
	/** Timer for blinking effect */
	float BlinkTimer = 0.f;
	
	bool bIsLowHealth = false;

	/** Toggle for blink color state */
	bool bBlinkTurningRed = true;

	// Colors for transition
	FLinearColor CurrentColor = FLinearColor::Black;
	FLinearColor TargetColor = FLinearColor::Red;

	// Interpolation speed
	UPROPERTY(EditAnywhere, Category = "HealthBar", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float ColorChangeSpeed = 5.f;

	/** Handle the blinking effect when health is low */
	void LowHealthBlink();
};