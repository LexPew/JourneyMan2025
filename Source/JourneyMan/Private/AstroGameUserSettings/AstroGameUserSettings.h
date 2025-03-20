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
	UPROPERTY(config)
	int32 SoundEffectVolume;
	// Incase I did sound wrong! - Sound might be multiplyer this is just here incase it needed to be treated like that.
	/*UPROPERTY(config)
	//float MasterVolume;
	//UPROPERTY(config)
	float SoundEffectVolume;*/

	// Accessibility

public:
	// User-facing
	// Display
	// Get the saved DisplayID
	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Display")
	int32 GetDisplayID() const;
	// Set a new DisplayID
	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Display")
	void SetDisplayID(int32 NewDisplayID);
	
	// Control
	// Get the current mouse sensitivity
	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Control")
	FVector2D GetMouseSensitivity() const;
	// Set a new mouse sensitivity value
	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Control")
	void SetMouseSensitivity(FVector2D NewMouseSensitivity);
	
	// Sound
	// Get the new master volume level
	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Sound")
	int32 GetMasterVolume() const;
	/*UFUNCTION(BlueprintCallable, Category = "Settings|Config|Sound")
	float GetMasterVolume() const;*/
	// Set a new master volume level
	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Sound")
	void SetMasterVolume(int32 NewMasterVolume);
	/*UFUNCTION(BlueprintCallable, Category = "Settings|Config|Sound")
	void SetMasterVolume(float NewMasterVolume);*/
	// Get the new sound effect volume level
	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Sound")
	int32 GetSoundEffectVolume() const;
	/*UFUNCTION(BlueprintCallable, Category = "Settings|Config|Sound")
	float GetSoundEffectVolume() const;*/
	// Set a new sound effect volume level
	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Sound")
	void SetSoundEffectVolume(int32 NewSoundEffectVolume);
	/*UFUNCTION(BlueprintCallable, Category = "Settings|Config|Sound")
	void SetSoundEffectVolume(float NewSoundEffectVolume);*/

	// Internal
	// Gets the game user settings, but cast as this (Make sure this is set as the GameUserSettingsClassName in /Script/Engine.Engine!)
	UFUNCTION(BlueprintCallable, Category = "Settings")
	static UAstroGameUserSettings* GetAstroGameUserSettings();

	// Sets the current resolution to a new value, but does not set as the last confirmed value. Make sure to use either ConfirmResolution or Revert Resolution!
	UFUNCTION(BlueprintCallable, Category = "Settings|Display")
	void TestNewResolution(FIntPoint NewResolution);
	// Sets the current resolution as the last known good one
	UFUNCTION(BlueprintCallable, Category = "Settings|Display")
	void ConfirmResolution(bool bCheckForCommandLineOverrides);
	// Sets the current resolution back to the last known good one
	UFUNCTION(BlueprintCallable, Category = "Settings|Display")
	void RevertResolution(bool bCheckForCommandLineOverrides);
};
