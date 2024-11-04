// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilityTreeHUD.generated.h"


class UMessageWidget;
class UAbilityBranch;
class AUTAD_UI_FPSCharacter;
/**********************ABILITY INFO STRUCTS***********************/
USTRUCT(BlueprintType)
struct FAbilityNodeInfo
{
	GENERATED_BODY()

	FAbilityNodeInfo(): Cost(0), bIsUnlock(false)
	{
	}

	FAbilityNodeInfo(const FString& _TextName,int32 _Cost,bool _bIsUnlock)
	:TextName(_TextName),
	Cost(0),
	bIsUnlock(false)
	
	{
	}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityTreeInfo)
	FString TextName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityTreeInfoUI)
	int32 Cost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityTreeInfo)
	bool bIsUnlock;
};

USTRUCT(BlueprintType)
struct FAbilityBranchInfo
{
	GENERATED_BODY()

	FAbilityBranchInfo(){}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityTreeInfo)
	FString BranchName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilityTreeInfo)
	TArray<FAbilityNodeInfo> AbilityNodesInfoArray;
};

/*****************************************************************/

class UHorizontalBox;
/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UAbilityTreeHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable, Category = "Visibility")
	void Show();
	
	UFUNCTION(BlueprintCallable, Category = "Visibility")
	void Hide();

	// Constructor
	UAbilityTreeHUD(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the widget is constructed
	virtual void NativeConstruct() override;

public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<UAbilityNode> AbilityNodeWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<UAbilityBranch> AbilityBranchWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	FMargin BranchesPadding;

	// Horizontal box to hold the branches
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* TreeContainer;

	UPROPERTY(meta = (BindWidget))
	UMessageWidget* MessageWidget;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CoinsText;

	// Add an ability branch
	UFUNCTION(BlueprintCallable, Category="Ability Tree")
	void AddBranch(FAbilityBranchInfo BranchInfo);

	// Remove an ability branch
	UFUNCTION(BlueprintCallable, Category="Ability Tree")
	void RemoveBranch(UAbilityBranch* BranchToRemove);
	
	UAbilityBranch* ReadfromStructInfo(FAbilityBranchInfo BranchInfo);

	int32& GetCurrencyFromPlayer();

	void SetPlayerCurrency(int32 newCurrency);

	void DisplayMessage(FString Message, float DisplayTime);

	void SetCoinsText(int32 coins);

private:
	AUTAD_UI_FPSCharacter * FPSCharacter ;
	
};
