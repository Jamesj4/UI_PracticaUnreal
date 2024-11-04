// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityNode.h"

#include <string>

#include "AbilityBranch.h"
#include "AbilityTreeHUD.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

UAbilityNode::UAbilityNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer),
                                                                         PurchaseButton(nullptr),
                                                                         AbilityNameText(nullptr),
                                                                         AbilityCostText(nullptr),
                                                                         ParentAbilityNode(nullptr), AbilityCost(0),
                                                                         HoldProgressBar(nullptr),
                                                                         bIsUnlocked(false),
                                                                         AbilityBranchParent(nullptr)
{
}

void UAbilityNode::NativeConstruct()
{
	Super::NativeConstruct();

	if (PurchaseButton)
	{
		PurchaseButton->OnPressed.AddDynamic(this, &UAbilityNode::OnPurchasePressed);
		PurchaseButton->OnReleased.AddDynamic(this, &UAbilityNode::OnPurchaseReleased);
	}
}


void UAbilityNode::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// If the button is being held, update the hold progress
	if (bIsHolding)
	{
		HoldProgress += InDeltaTime / HoldDuration;

		// Update progress bar
		if (HoldProgressBar)
		{
			HoldProgressBar->SetPercent(HoldProgress);
		}

		// If fully held, confirm the purchase
		if (HoldProgress >= 1.0f)
		{
			ConfirmPurchase();
			HoldProgress = 0.0f;
			bIsHolding = false;
		}
	}
}
void UAbilityNode::Init(FAbilityNodeInfo Info,UAbilityBranch * _AbilityBranchParent)
{
	if(AbilityNameText)
	{
		AbilityNameText->SetText(FText::FromString(Info.TextName));
	}

	if(AbilityCostText)
	{
		AbilityCost= Info.Cost;
		
		FString CostString = FString::Printf(TEXT("%d"), AbilityCost);
		AbilityCostText->SetText(FText::FromString(CostString));
	}

	bIsUnlocked = Info.bIsUnlock;
	if (bIsUnlocked && PurchaseButton)
	{
		PurchaseButton->OnPressed.RemoveDynamic(this, &UAbilityNode::OnPurchasePressed);
		PurchaseButton->OnReleased.RemoveDynamic(this, &UAbilityNode::OnPurchaseReleased);
		PurchaseButton->SetIsEnabled(false);
	}

	AbilityBranchParent =_AbilityBranchParent;


	if (HoldProgressBar)
	{
		HoldProgressBar->SetPercent(bIsUnlocked ? 1.0f : 0.0f);
	}
}

bool UAbilityNode::CanBuy(int32 AvailableCurrency) const
{
	if(AvailableCurrency < AbilityCost)
	{

		AbilityBranchParent->ParentTree->DisplayMessage(FString::Printf(TEXT("You dont have enough coins \n Need: %d , Have : %d"), AbilityCost,AvailableCurrency), 2.f);
	
		return false;
	}
		
	if (ParentAbilityNode)
	{
		// If the parent exists and is unlocked, this node can be bought
		if (ParentAbilityNode->IsUnlocked())
		{
			return true;
		}
		
		AbilityBranchParent->ParentTree->DisplayMessage("Parent node is locked; cannot purchase this ability.",2.f);

		return false;
		
	}

	return true;
}


void UAbilityNode::TryToPurchase(int32& AvailableCurrency)
{
	
	if (CanBuy(AvailableCurrency))
	{
		// ACTION OF BUY WAS SUCCESS
		AvailableCurrency -= AbilityCost;

		AbilityBranchParent->ParentTree->SetCoinsText(AvailableCurrency);
		AbilityBranchParent->ParentTree->SetPlayerCurrency(AvailableCurrency);
		bIsUnlocked = true;
		HoldProgressBar->SetPercent(1);


		if (PurchaseButton)
		{
			PurchaseButton->OnPressed.RemoveDynamic(this, &UAbilityNode::OnPurchasePressed);
			PurchaseButton->OnReleased.RemoveDynamic(this, &UAbilityNode::OnPurchaseReleased);
			PurchaseButton->SetIsEnabled(false);
		}

		AbilityBranchParent->ParentTree->DisplayMessage(FString::Printf(TEXT("The Ability %s has been bought"), *AbilityNameText->GetText().ToString()), 2.f);
	
	}
}

void UAbilityNode::OnPurchasePressed()
{
	int32 AvailableCurrency = 0;
	
	if(AbilityBranchParent->ParentTree && AbilityBranchParent->ParentTree)
	{
		AvailableCurrency = AbilityBranchParent->ParentTree->GetCurrencyFromPlayer();
	}
	if (!bIsUnlocked && CanBuy(AvailableCurrency))
	{
		bIsHolding = true;
		HoldProgress = 0.0f; // Reset progress on button press
	}
}


void UAbilityNode::OnPurchaseReleased()
{
	
	// Reset if released early
	bIsHolding = false;
	HoldProgress = 0.0f; 
	if (HoldProgressBar)
	{
		HoldProgressBar->SetPercent(0.0f); // Reset progress bar UI
	}
}

void UAbilityNode::ConfirmPurchase()
{
	if (bIsHolding)
	{
		int32 AvailableCurrency = 0;
	
		if(AbilityBranchParent->ParentTree && AbilityBranchParent->ParentTree)
		{
			AvailableCurrency = AbilityBranchParent->ParentTree->GetCurrencyFromPlayer();
		}


		TryToPurchase(AvailableCurrency);
	}
}



