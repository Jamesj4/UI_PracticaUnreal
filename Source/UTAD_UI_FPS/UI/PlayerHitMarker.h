// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VisibilityInterface.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHitMarker.generated.h"

/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UPlayerHitMarker : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Visibility")
	void Show();
	
	UFUNCTION(BlueprintCallable, Category = "Visibility")
	void Hide();
	
	UFUNCTION()
	void OnTakeDamage();
	

protected:
	
	virtual void NativeConstruct() override;
	
	virtual void NativeDestruct() override;
private:

private:

	FTimerHandle HitMarkerTimerHandle;
	const float HitMarkerDisplayDuration = 0.5f;
	bool bIsHitMarkerVisible = false;
	
};