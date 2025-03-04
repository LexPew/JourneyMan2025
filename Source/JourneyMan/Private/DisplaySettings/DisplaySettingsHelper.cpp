// Fill out your copyright notice in the Description page of Project Settings.


#include "DisplaySettings/DisplaySettingsHelper.h"

FText UDisplaySettingsHelper::GetDisplayName(int DisplayID)
{
	FDisplayMetrics DisplayMetrics;

	FDisplayMetrics::RebuildDisplayMetrics(DisplayMetrics);

	return FText::FromString(DisplayMetrics.MonitorInfo[DisplayID].Name);
}

TArray<FText> UDisplaySettingsHelper::GetAllDisplayNames()
{
	FDisplayMetrics DisplayMetrics;

	FDisplayMetrics::RebuildDisplayMetrics(DisplayMetrics);

	TArray<FText> MonitorNames;

	for (int i = 0; i < DisplayMetrics.MonitorInfo.Num(); i++)
	{
		MonitorNames.Add(FText::FromString(DisplayMetrics.MonitorInfo[i].Name));
	}

	return MonitorNames;
}
