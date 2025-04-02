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
	UFUNCTION(BlueprintCallable, Category = "Settings|Display", meta = (DeprecatedFunction, DeprecationMessage = "Please use GetAllDisplayNamesPure instead"))
	// Gets the names of all displays connected
	static TArray<FText> GetAllDisplayNames();
	/* Pure version of GetAllDisplayNames */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Settings|Display")
	static TArray<FText> GetAllDisplayNamesPure();
	UFUNCTION(BlueprintCallable, Category = "Settings|Display")
	// Gets the name of the current display
	static FText GetCurrentDisplayName();
	UFUNCTION(BlueprintCallable, Category = "Settings|Display")
	// Moves the game window to the display with the given ID
	static void MoveGameToDisplay(int32 DisplayID);
	// Gets the max resolution of the display with the given displayID
	UFUNCTION(BlueprintCallable, Category = "Settings|Display")
	static FIntPoint GetDisplayMaxResolution(int32 DisplayID);
	// Gets the primary monitor's ID
	UFUNCTION(BlueprintCallable, Category = "Settings|Display")
	static int32 GetPrimaryDisplayID();
	/* Move a windowed window to the centre of a display */
	UFUNCTION(BlueprintCallable, Category = "Settings|Display")
	static void MoveWindowedWindowToCentre(int32 DisplayID, FIntPoint WindowDimensions);

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
