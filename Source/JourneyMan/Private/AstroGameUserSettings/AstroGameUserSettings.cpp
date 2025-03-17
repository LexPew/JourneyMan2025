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

void UAstroGameUserSettings::SetMasterVolume(int32 NewMasterVolume)
{
	MasterVolume = NewMasterVolume;
}

UAstroGameUserSettings* UAstroGameUserSettings::GetAstroGameUserSettings()
{
	return Cast<UAstroGameUserSettings>(GEngine->GetGameUserSettings());
}
