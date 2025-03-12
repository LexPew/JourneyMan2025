// Fill out your copyright notice in the Description page of Project Settings.


#include "AstroGameUserSettings/AstroGameUserSettings.h"

int32 UAstroGameUserSettings::GetDisplayID() const
{
	return DisplayID;
}

UAstroGameUserSettings* UAstroGameUserSettings::GetAstroGameUserSettings()
{
	return Cast<UAstroGameUserSettings>(GEngine->GetGameUserSettings());
}
