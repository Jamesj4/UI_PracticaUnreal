// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityBranch.h"

#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/Image.h"
#include "AbilityNode.h"
#include "Components/TextBlock.h"

class UImage;

UAbilityBranch::UAbilityBranch(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


UImage* UAbilityBranch::CreateScaledImageWidget()
{
	// Create an image widget
	UImage* ImageWidget = NewObject<UImage>(this);
    
	if (ImageWidget)
	{
	
		FSlateBrush NewBrush = ImageWidget->GetBrush();
		NewBrush.ImageSize = FVector2D(16.0f, 40.0f);
		ImageWidget->SetBrush(NewBrush);

		// Return the configured image
		return ImageWidget;
		
	}

	return nullptr;
}
void UAbilityBranch::AddAbilityNode(UAbilityNode* AbilityNode)
{
	if(!AbilityNodes.IsEmpty())
	{
		AbilityNode->ParentAbilityNode = AbilityNodes.Last();

		//Add some kind of separator
		if(UImage* Separator = CreateScaledImageWidget())
		{
			if (UVerticalBoxSlot* SeparatorSlot = AbilityContainer->AddChildToVerticalBox(Separator))
			{
				// Adjust the slot properties
				SeparatorSlot->SetHorizontalAlignment(HAlign_Center); 
				SeparatorSlot->SetVerticalAlignment(VAlign_Center);   
			}
		}
		
	}
	AbilityNodes.Add(AbilityNode);

	if (UVerticalBoxSlot* AbilityNodeBox = AbilityContainer->AddChildToVerticalBox(AbilityNode))
	{
		// Adjust the slot properties
		AbilityNodeBox->SetHorizontalAlignment(HAlign_Fill); 
		AbilityNodeBox->SetVerticalAlignment(VAlign_Center);
		AbilityNodeBox->SetPadding(FMargin(10,0));
	}
	
}

void UAbilityBranch::InitBranch(FString Name,UAbilityTreeHUD* _ParentTree)
{
	if(BranchTitleText)
	{
		BranchTitleText->SetText(FText::FromString(Name));
	}

	ParentTree = _ParentTree;
}

void UAbilityBranch::NativeConstruct()
{
	Super::NativeConstruct();

	// Clear the AbilityNodes array to ensure no duplicates
	AbilityNodes.Empty();


	

}

