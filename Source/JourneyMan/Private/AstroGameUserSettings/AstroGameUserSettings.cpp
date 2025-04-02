// Fill out your copyright notice in the Description page of Project Settings.


#include "AstroGameUserSettings/AstroGameUserSettings.h"

int32 UAstroGameUserSettings::GetDisplayID() const
{
	return DisplayID;
}

void UAstroGameUserSettings::SetDisplayID(int32 NewDisplayID)
{
	DisplayID = NewDisplayID;
}

TArray<FText> UAstroGameUserSettings::GetDisplayNames() const
{
	return DisplayNames;
}

void UAstroGameUserSettings::SetDisplayNames(TArray<FText> NewDisplayNames)
{
	DisplayNames = NewDisplayNames;
}

int32 UAstroGameUserSettings::GetDisplay() const
{
	return Display;
}

void UAstroGameUserSettings::SetDisplay(int32 NewDisplay)
{
	Display = NewDisplay;
}

int32 UAstroGameUserSettings::GetLastConfirmedDisplay() const
{
	return LastConfirmedDisplay;
}

void UAstroGameUserSettings::SetLastConfirmedDisplay(int32 NewLastConfirmedDisplay)
{
	LastConfirmedDisplay = NewLastConfirmedDisplay;
}

FVector2D UAstroGameUserSettings::GetMouseSensitivity() const
{
	return MouseSensitivity;
}

void UAstroGameUserSettings::SetMouseSensitivity(FVector2D NewMouseSensitivity)
{
	MouseSensitivity = NewMouseSensitivity;
}

int32 UAstroGameUserSettings::GetMasterVolume() const
{
	return MasterVolume;
}

/*float UAstroGameUserSettings::GetMasterVolume() const
{
	return MasterVolume;
}*/

void UAstroGameUserSettings::SetMasterVolume(int32 NewMasterVolume)
{
	MasterVolume = NewMasterVolume;
}

/*void UAstroGameUserSettings::SetMasterVolume(float NewMasterVolume)
{
	MasterVolume = NewMasterVolume;
}*/

int32 UAstroGameUserSettings::GetMusicVolume() const
{
	return MusicVolume;
}

/*float UAstroGameUserSettings::GetMusicVolume() const
{
	return MusicVolume;
}*/

void UAstroGameUserSettings::SetMusicVolume(int32 NewMusicVolume)
{
	MusicVolume = NewMusicVolume;
}

/*void UAstroGameUserSettings::SetMusicVolume(float NewMusicVolume)
{
	MusicVolume = NewMusicVolume;
}*/

int32 UAstroGameUserSettings::GetSoundEffectVolume() const
{
	return SoundEffectVolume;
}

/*float UAstroGameUserSettings::GetSoundEffectVolume() const
{
	return SoundEffectVolume;
}*/

void UAstroGameUserSettings::SetSoundEffectVolume(int32 NewSoundEffectVolume)
{
	SoundEffectVolume = NewSoundEffectVolume;
}

/*void UAstroGameUserSettings::SetSoundEffectVolume(float NewSoundEffectVolume)
{
	SoundEffectVolume = NewSoundEffectVolume;
}*/

UAstroGameUserSettings* UAstroGameUserSettings::GetAstroGameUserSettings()
{
	return Cast<UAstroGameUserSettings>(GEngine->GetGameUserSettings());
}

void UAstroGameUserSettings::ValidateAstroUserSettings()
{
	// Determine if the display settings have changed
	if (DisplayNames.Num() == 0)
	{
		UE_LOG(LogTemp, Log, TEXT("No Displays in DispayName array."))
		return;
	}
	
	bool bSettingsChanged = false;

	// If the number of displays is different then there is obviously a change
	if (DisplayNames.Num() != UDisplaySettingsHelper::GetAllDisplayNames().Num())
	{
		bSettingsChanged = true;
	}
	// if the above is true then there must be the same number of monitors, so we should compare the names of each one.
	else
	{
		for (int32 i = 0; i < DisplayNames.Num(); i++)
		{
			if (!FTextComparison::EqualToCaseIgnored(DisplayNames[i].ToString(), UDisplaySettingsHelper::GetAllDisplayNames()[i].ToString()))
			{
				bSettingsChanged = true;
			}
		}
	}

	if (bSettingsChanged)
	{
		// Set displays back to the primary display
		Display = UDisplaySettingsHelper::GetPrimaryDisplayID();
		LastConfirmedDisplay = UDisplaySettingsHelper::GetPrimaryDisplayID();

		// Set saved resolution to new display's resolution
		FIntPoint TmpIntPoint = FIntPoint(UDisplaySettingsHelper::GetDisplayMaxResolution(Display));
		ResolutionSizeX = TmpIntPoint.X;
		ResolutionSizeY = TmpIntPoint.Y;
		DesiredScreenWidth = TmpIntPoint.X;
		DesiredScreenHeight = TmpIntPoint.Y;
		LastUserConfirmedResolutionSizeX = TmpIntPoint.X;
		LastUserConfirmedResolutionSizeY = TmpIntPoint.Y;
		LastUserConfirmedDesiredScreenWidth = TmpIntPoint.X;
		LastUserConfirmedDesiredScreenHeight = TmpIntPoint.Y;

		ApplyResolutionSettings(true);
	}

	// What if the user intentionally set the resolution to be lower than the max resolution?
	/*if (FIntPoint(ResolutionSizeX, ResolutionSizeY) == UDisplaySettingsHelper::GetCurrentDisplayResolution(Display))
	{

	}*/

	return;
}

bool UAstroGameUserSettings::IsDisplayDirty() const
{
	if (Display != LastConfirmedDisplay)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void UAstroGameUserSettings::ConfirmDisplay()
{
	LastConfirmedDisplay = Display;
}

void UAstroGameUserSettings::RevertDisplay()
{
	Display = LastConfirmedDisplay;
}

void UAstroGameUserSettings::TestNewResolution(FIntPoint NewResolution)
{
	UAstroGameUserSettings::ResolutionSizeX = NewResolution.X;
	UAstroGameUserSettings::ResolutionSizeY = NewResolution.Y;

	UAstroGameUserSettings::DesiredScreenWidth = NewResolution.X;
	UAstroGameUserSettings::DesiredScreenHeight = NewResolution.Y;
}

void UAstroGameUserSettings::ConfirmResolution(bool bCheckForCommandLineOverrides)
{
	UAstroGameUserSettings::LastUserConfirmedResolutionSizeX = UAstroGameUserSettings::ResolutionSizeX;
	UAstroGameUserSettings::LastUserConfirmedResolutionSizeY = UAstroGameUserSettings:: ResolutionSizeY;

	UAstroGameUserSettings::LastUserConfirmedDesiredScreenWidth = UAstroGameUserSettings::DesiredScreenWidth;
	UAstroGameUserSettings::LastUserConfirmedDesiredScreenHeight = UAstroGameUserSettings::DesiredScreenHeight;

	ApplyResolutionSettings(bCheckForCommandLineOverrides);
}

void UAstroGameUserSettings::RevertResolution(bool bCheckForCommandLineOverrides)
{
	UAstroGameUserSettings::ResolutionSizeX = UAstroGameUserSettings::LastUserConfirmedResolutionSizeX;
	UAstroGameUserSettings::ResolutionSizeY = UAstroGameUserSettings::LastUserConfirmedResolutionSizeY;

	UAstroGameUserSettings::DesiredScreenWidth = UAstroGameUserSettings::LastUserConfirmedDesiredScreenWidth;
	UAstroGameUserSettings::DesiredScreenHeight = UAstroGameUserSettings::LastUserConfirmedDesiredScreenHeight;

	ApplyResolutionSettings(bCheckForCommandLineOverrides);
}
