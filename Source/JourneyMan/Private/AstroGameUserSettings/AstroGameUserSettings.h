// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "AstroGameUserSettings.generated.h"

/**
 * 
 */
UCLASS(config = GameUserSettings, configdonotcheckdefaults, MinimalAPI)
class UAstroGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

private:
	// Display
	UPROPERTY(config)
	int32 DisplayID;

	// Control
	UPROPERTY(config)
	FVector2D MouseSensitivity;

	// Sound
	UPROPERTY(config)
	int32 MasterVolume;

	// Accessibility

public:
	// User-facing
	// Display
	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Display")
	int32 GetDisplayID() const;
	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Display")
	void SetDisplayID(int32 NewDisplayID);
	
	// Control
	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Control")
	FVector2D GetMouseSensitivity() const;
	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Control")
	void SetMouseSensitivity(FVector2D NewMouseSensitivity);
	
	// Sound
	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Sound")
	int32 GetMasterVolume() const;
	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Sound")
	void SetMasterVolume(int32 NewMasterVolume);

	// Internal
	UFUNCTION(BlueprintCallable, Category = "Settings")
	static UAstroGameUserSettings* GetAstroGameUserSettings();
};
