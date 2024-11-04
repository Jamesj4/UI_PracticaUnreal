// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilityNode.generated.h"


struct FAbilityNodeInfo;
class UAbilityBranch;
class UButton;
class UProgressBar;
/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UAbilityNode : public UUserWidget
{
	GENERATED_BODY()
public:
	// Constructor
	UAbilityNode(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the widget is constructed
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


public:

	void Init(FAbilityNodeInfo Info,UAbilityBranch * _AbilityBranchParent);
	
	// Determines if the ability can be bought
	UFUNCTION(BlueprintCallable, Category="Ability")
	bool CanBuy(int32 AvailableCurrency) const;
	void TryToPurchase(int32& AvailableCurrency);
	UFUNCTION()
	void OnPurchasePressed();

	UFUNCTION()
	void OnPurchaseReleased();
	void ConfirmPurchase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability")
	float HoldDuration = 2.0f;
	
	UPROPERTY(meta = (BindWidget))
	UButton* PurchaseButton;

	// Widget text for the ability name
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AbilityNameText;

	// Widget text for the ability cost
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AbilityCostText;

	// Parent ability node
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability")
	UAbilityNode* ParentAbilityNode;
	
	// Cost of the ability
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability")
	int32 AbilityCost;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HoldProgressBar;

	bool IsUnlocked(){ return bIsUnlocked;}

private:

	// Timer to track hold duration
	FTimerHandle HoldTimerHandle;
	
	bool bIsUnlocked;

	bool bIsHolding = false;

	float HoldProgress = 0.0f;
	


	UPROPERTY()
	UAbilityBranch * AbilityBranchParent;
};
