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
	// Gets the name of a display at the provided ID
	static FText GetDisplayName(int DisplayID = 0);
	UFUNCTION(BlueprintCallable, Category = "Settings|Display")
	// Gets the names of all displays connected
	static TArray<FText> GetAllDisplayNames();
	UFUNCTION(BlueprintCallable, Category = "Settings|Display")
	// Gets the name of the current display
	static FText GetCurrentDisplayName();
	UFUNCTION(BlueprintCallable, Category = "Settings|Display")
	// Moves the game window to the display with the given ID
	static void MoveGameToDisplay(int32 DisplayID);

	// Debug
	UFUNCTION(BlueprintCallable, Category = "Settings|Display|Debug")
	// Prints all display IDs to the screen and to LogTemp
	static void PrintAllDisplayIDs();
	UFUNCTION(BlueprintCallable, Category = "Settings|Display|Debug")
	// Prints the left-most position out of all the displays to the screen and to LogTemp
	static void PrintVirtualDisplayRect();
	UFUNCTION(BlueprintCallable, Category = "Settings|Display|Debug")
	// Prints the left position off all the connected monitors to the screen and to LogTemp
	static void PrintAllMonitorDisplayRects();
	UFUNCTION(BlueprintCallable, Category = "Settings|Display|Debug")
	// Prints the top left position of the game window to the screen and to LogTemp
	static void PrintWindowScreenPosition();
};
