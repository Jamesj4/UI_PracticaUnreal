// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VisibilityInterface.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHealthBar.generated.h"


class UProgressBar;
/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UEnemyHealthBar : public UUserWidget,  public IVisibilityInterface
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Visibility")
	virtual void Show_Implementation() override;
	
	UFUNCTION(BlueprintCallable, Category = "Visibility")
	virtual void Hide_Implementation() override;
	UFUNCTION()
	void UpdateEnemyHealthBar(int NewHealth, int MaxHealth);
protected:
	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthProgressBarWidget;

};
	