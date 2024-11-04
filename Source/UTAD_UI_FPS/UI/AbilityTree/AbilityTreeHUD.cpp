// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTreeHUD.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "AbilityBranch.h"
#include "AbilityNode.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "UTAD_UI_FPS/UTAD_UI_FPSCharacter.h"
#include "UTAD_UI_FPS/UI/MessageWidget.h"

void UAbilityTreeHUD::Show()
{
	SetVisibility(ESlateVisibility::Visible);

	if(FPSCharacter)
	{
		SetCoinsText(FPSCharacter->NumberOfCoins);
	}
}

void UAbilityTreeHUD::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
}

UAbilityTreeHUD::UAbilityTreeHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UAbilityTreeHUD::NativeConstruct()
{
	Super::NativeConstruct();

	// Ensure that the horizontal box is bound
	if (!TreeContainer)
	{
		UE_LOG(LogTemp, Warning, TEXT("BranchContainer is not bound! Make sure it is set in the Blueprint."));
	}

	FPSCharacter = Cast<AUTAD_UI_FPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
}

void UAbilityTreeHUD::AddBranch(FAbilityBranchInfo BranchInfo)
{

	UAbilityBranch* NewBranch = ReadfromStructInfo(BranchInfo);
	
	// Check if the new branch and container are valid
	if (NewBranch && TreeContainer)
	{
		NewBranch->SetPadding(BranchesPadding);
		
		// Add the branch widget to the horizontal box
		if(UHorizontalBoxSlot* HorizontalBoxSlot = TreeContainer->AddChildToHorizontalBox(NewBranch))
		{
			HorizontalBoxSlot->SetVerticalAlignment(VAlign_Fill);
			HorizontalBoxSlot->SetPadding(FMargin(5,0));
			UE_LOG(LogTemp, Log, TEXT("Added new branch to AbilityTreeHUD."));
		}

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to add branch: Branch or BranchContainer is invalid."));
	}
}

void UAbilityTreeHUD::RemoveBranch(UAbilityBranch* BranchToRemove)
{
	
	if (BranchToRemove && TreeContainer)
	{
		// Remove the branch widget from the horizontal box
		TreeContainer->RemoveChild(BranchToRemove);
		UE_LOG(LogTemp, Log, TEXT("Removed branch from AbilityTreeHUD."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to remove branch: Branch or BranchContainer is invalid."));
	}
}

UAbilityBranch* UAbilityTreeHUD::ReadfromStructInfo(FAbilityBranchInfo BranchInfo)
{
	if(!AbilityNodeWidget || !AbilityBranchWidget) return nullptr;


	UAbilityBranch* newBranch = CreateWidget<UAbilityBranch>(GetWorld(), AbilityBranchWidget);
	newBranch->InitBranch(BranchInfo.BranchName,this);
	for(FAbilityNodeInfo NodeInfo :BranchInfo.AbilityNodesInfoArray)
	{
		UAbilityNode* AbilityNode = CreateWidget<UAbilityNode>(GetWorld(), AbilityNodeWidget);
		AbilityNode->Init(NodeInfo,newBranch);
		newBranch->AddAbilityNode(AbilityNode);
	}
	
	return newBranch;
}

int32& UAbilityTreeHUD::GetCurrencyFromPlayer()
{

	return FPSCharacter->GetNumberOfCoins();

}

void UAbilityTreeHUD::SetPlayerCurrency(int32 newCurrency)
{
	return FPSCharacter->SetNumberOfCoins(newCurrency);
}

void UAbilityTreeHUD::DisplayMessage(FString Message, float DisplayTime)
{
	if (MessageWidget)
	{
		
		MessageWidget->ShowMessage(Message,DisplayTime);

	}
}

void UAbilityTreeHUD::SetCoinsText(int32 coins)
{
	if(CoinsText)
	{
		CoinsText->SetText(FText::FromString(FString::FromInt(coins)));
	}
}
