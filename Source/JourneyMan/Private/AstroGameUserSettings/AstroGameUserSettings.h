// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "DisplaySettings/DisplaySettingsHelper.h"
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
	/* Please use the new CurrentDisplay, and LastConfirmedDisplay so we can rollback like other display settings can*/
	UPROPERTY(config, meta = (DeprecatedProperty, DeprecationMessage = "Please use Display and LastConfirmedDisplay to store display information!"))
	int32 DisplayID;

	/* Array of last connected display names to see if displays have changed */
	UPROPERTY(config)
	TArray<FText> DisplayNames;
	/* Store current display ID */
	UPROPERTY(config)
	int32 Display;
	/* Store last display ID (May be identical to the current one) - Don't rely on this one to be good */
	UPROPERTY(config)
	int32 LastConfirmedDisplay;

	// Control
	UPROPERTY(config)
	FVector2D MouseSensitivity;

	// Sound
	// This treats sound like its min 0 max 100
	/*UPROPERTY(config)
	int32 MasterVolume;
	UPROPERTY(config)
	int32 MusicVolume;
	UPROPERTY(config)
	int32 SoundEffectVolume;*/
	// Incase I did sound wrong! - Sound might be multiplyer this is just here incase it needed to be treated like that.
	// ... The music is far too loud lets try treating it as a multiplyer instead
	UPROPERTY(config)
	float MasterVolume;
	UPROPERTY(config)
	float MusicVolume;
	UPROPERTY(config)
	float SoundEffectVolume;

	// Accessibility

public:
	// User-facing
	// Display
	// Get the saved DisplayID
	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Display", meta = (DeprecatedFunction, DeprecationMessage = "Please use GetDisplay()"))
	int32 GetDisplayID() const;
	// Set a new DisplayID
	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Display", meta = (DeprecatedFunction, DeprecationMessage = "Please use SetDisplay() with ApplyDisplay()/RevertDisplay()"))
	void SetDisplayID(int32 NewDisplayID);
	
	/* Get the currently saved display names array */
	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Display")
	TArray<FText> GetDisplayNames() const;
	/* Set the currently saved display names array */
	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Display")
	void SetDisplayNames(TArray<FText> NewDisplayNames);

	/* Get the current display */
	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Display")
	int32 GetDisplay() const;
	/* Set the current display */
	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Display")
	void SetDisplay(int32 NewDisplay);

	/* Get the last confirmed display */
	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Display")
	int32 GetLastConfirmedDisplay() const;
	/* Set the last confirmed display - Try not to call this directly. Try to use RevertDisplayChange() instead! */
	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Display")
	void SetLastConfirmedDisplay(int32 NewLastConfirmedDisplay);

	// Control
	// Get the current mouse sensitivity
	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Control")
	FVector2D GetMouseSensitivity() const;
	// Set a new mouse sensitivity value
	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Control")
	void SetMouseSensitivity(FVector2D NewMouseSensitivity);
	
	// Sound
	// Get the new master volume level
	/*UFUNCTION(BlueprintCallable, Category = "Settings|Config|Sound")
	int32 GetMasterVolume() const;*/
	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Sound")
	float GetMasterVolume() const;

	// Set a new master volume level
	/*UFUNCTION(BlueprintCallable, Category = "Settings|Config|Sound")
	void SetMasterVolume(int32 NewMasterVolume);*/
	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Sound")
	void SetMasterVolume(float NewMasterVolume);

	// Get the new music volume
	/*UFUNCTION(BlueprintCallable, Category = "Settings|Config|Sound")
	int32 GetMusicVolume() const;*/
	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Sound")
	float GetMusicVolume() const;

	// Set a new music volume
	/*UFUNCTION(BlueprintCallable, Category = "Settings|Config|Sound")
	void SetMusicVolume(int32 NewMusicVolume);*/
	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Sound")
	void SetMusicVolume(float NewMusicVolume);

	// Get the new sound effect volume level
	/*UFUNCTION(BlueprintCallable, Category = "Settings|Config|Sound")
	int32 GetSoundEffectVolume() const;*/
	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Sound")
	float GetSoundEffectVolume() const;

	// Set a new sound effect volume level
	/*UFUNCTION(BlueprintCallable, Category = "Settings|Config|Sound")
	void SetSoundEffectVolume(int32 NewSoundEffectVolume);*/
	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Sound")
	void SetSoundEffectVolume(float NewSoundEffectVolume);

	// Internal
	// Gets the game user settings, but cast as this (Make sure this is set as the GameUserSettingsClassName in /Script/Engine.Engine!)
	UFUNCTION(BlueprintCallable, Category = "Settings")
	static UAstroGameUserSettings* GetAstroGameUserSettings();

	/* Call ValidateSettings() as well! This function is only for validating astro-game specific extentions to GameUserSettings! */
	UFUNCTION(BlueprintCallable, Category = "Settings")
	void ValidateAstroUserSettings();

	/* Returns true if Display isn't equal to LastConfirmedDisplay */
	UFUNCTION(BlueprintCallable, Category = "Settings|Display")
	bool IsDisplayDirty() const;
	/* Sets the current resolution as the last known good one. Please apply once this has been called */
	UFUNCTION(BlueprintCallable, Category = "Settings|Display")
	void ConfirmDisplay();
	/* Sets the current display back to the last known good one. Please apply once this has been called */
	UFUNCTION(BlueprintCallable, Category = "Settings|Display")
	void RevertDisplay();

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
