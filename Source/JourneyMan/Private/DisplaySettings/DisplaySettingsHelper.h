// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "GenericPlatform/GenericApplication.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Framework/Application/SlateApplication.h"
#include "DisplaySettingsHelper.generated.h"

/**
 * 
 */
UCLASS()
class JOURNEYMAN_API UDisplaySettingsHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Settings|Display")
	static FText GetDisplayName(int DisplayID = 0);
	UFUNCTION(BlueprintCallable, Category = "Settings|Display")
	static TArray<FText> GetAllDisplayNames();
	UFUNCTION(BlueprintCallable, Category = "Settings|Display")
	// @TODO Does this work with only 1 monitor?
	static FText GetCurrentDisplay();
	// Make sure to take the game out of fullscreen before changing!
	UFUNCTION(BlueprintCallable, Category = "Settings|Display")
	static void MoveGameToDisplay(int32 DisplayID);

	// Debug
	UFUNCTION(BlueprintCallable, Category = "Settings|Display|Debug")
	static void PrintAllDisplayIDs();
	UFUNCTION(BlueprintCallable, Category = "Settings|Display|Debug")
	static void PrintVirtualDisplayRect();
	UFUNCTION(BlueprintCallable, Category = "Settings|Display|Debug")
	static void PrintAllMonitorDisplayRects();
	UFUNCTION(BlueprintCallable, Category = "Settings|Display|Debug")
	static void PrintScreenPosition();
};
