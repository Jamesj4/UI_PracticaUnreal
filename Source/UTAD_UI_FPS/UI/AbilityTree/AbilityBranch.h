// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilityBranch.generated.h"


class UAbilityNode;
class UAbilityTreeHUD;
class UVerticalBox;
class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UAbilityBranch : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Constructor
	UAbilityBranch(const FObjectInitializer& ObjectInitializer);
	UImage* CreateScaledImageWidget();

	void AddAbilityNode(UAbilityNode* AbilityNode);

	void InitBranch(FString Name,UAbilityTreeHUD* _ParentTree);
protected:
	// Called when the widget is constructed
	virtual void NativeConstruct() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	FMargin NodesPadding;
	
	// Title of the ability branch
	UPROPERTY(meta = (BindWidget))
	UTextBlock* BranchTitleText;

	// Vertical box to contain ability nodes
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* AbilityContainer;

	// List of ability widgets in this branch
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Abilities")
	TArray<UAbilityNode*> AbilityNodes;

	UPROPERTY()
	UAbilityTreeHUD* ParentTree;

	
};