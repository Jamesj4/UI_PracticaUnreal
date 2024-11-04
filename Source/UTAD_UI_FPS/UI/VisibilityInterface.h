// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "VisibilityInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UVisibilityInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UTAD_UI_FPS_API IVisibilityInterface
{
	GENERATED_BODY()

public:
	
	/** Show */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Visibility")
	 void Show();

	/** Hide */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Visibility")
	 void Hide();

};
