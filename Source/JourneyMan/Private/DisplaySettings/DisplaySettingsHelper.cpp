// Fill out your copyright notice in the Description page of Project Settings.


#include "DisplaySettings/DisplaySettingsHelper.h"

FText UDisplaySettingsHelper::GetDisplayName(int DisplayID)
{
	FDisplayMetrics DisplayMetrics;

	FDisplayMetrics::RebuildDisplayMetrics(DisplayMetrics);

	if (DisplayID < DisplayMetrics.MonitorInfo.Num())
	{
		return FText::FromString(DisplayMetrics.MonitorInfo[DisplayID].Name);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DisplaySettings: No monitor found with that ID"))
		return FText::FromString(TEXT("No monitor found with that ID"));
	}
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

FText UDisplaySettingsHelper::GetCurrentDisplayName()
{
	FDisplayMetrics DisplayMetrics;

	FDisplayMetrics::RebuildDisplayMetrics(DisplayMetrics);

	TArray<FVector2D> DisplayLocations;

	for (int32 i = 0; i < DisplayMetrics.MonitorInfo.Num(); i++)
	{
		DisplayLocations.Add(FVector2D(DisplayMetrics.MonitorInfo[i].DisplayRect.Left, DisplayMetrics.MonitorInfo[i].DisplayRect.Top));
	}

	int32 WindowX = FSlateApplication::Get().GetActiveTopLevelWindow()->GetPositionInScreen().X;

	// Find out which display the game window is on
	if (DisplayLocations.Num() > 1)
	{
		for (int i = 1; i < DisplayLocations.Num(); i++)
		{
			// @TODO Flawed in windowed mode. Order the DisplayLocations array first?
			if (WindowX < (DisplayLocations[i].X + 5)) // Offset because unreal places the window at 3, 0 when in windowed I think
			{
				return FText::FromString(DisplayMetrics.MonitorInfo[i].Name);
			}
		}
	}

	return FText::FromString(DisplayMetrics.MonitorInfo[0].Name);
}

void UDisplaySettingsHelper::MoveGameToDisplay(int32 DisplayID)
{
	FDisplayMetrics DisplayMetrics;

	FDisplayMetrics::RebuildDisplayMetrics(DisplayMetrics);

	TArray<FVector2D> DisplayLocations;

	for (int32 i = 0; i < DisplayMetrics.MonitorInfo.Num(); i++)
	{
		DisplayLocations.Add(FVector2D(DisplayMetrics.MonitorInfo[i].DisplayRect.Left, DisplayMetrics.MonitorInfo[i].DisplayRect.Top));
	}

	if (DisplayID >= DisplayLocations.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("DisplayID out of bounds of the array"));
		return;
	}

	FVector2D NewLocation = DisplayLocations[DisplayID];

	TSharedPtr<FGenericWindow> Window = FSlateApplication::Get().GetActiveTopLevelWindow()->GetNativeWindow();

	if (Window.IsValid())
	{
		Window->MoveWindowTo(NewLocation.X, NewLocation.Y);
	}

}

void UDisplaySettingsHelper::PrintAllDisplayIDs()
{
	if (GEngine)
	{
		FDisplayMetrics DisplayMetrics;

		FDisplayMetrics::RebuildDisplayMetrics(DisplayMetrics);

		for (int i = 0; i < DisplayMetrics.MonitorInfo.Num(); i++)
		{
			UE_LOG(LogTemp, Log, TEXT("Left: %s"), *DisplayMetrics.MonitorInfo[i].ID);
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::White, FString::Printf(TEXT("Left = %s"), *DisplayMetrics.MonitorInfo[i].ID));
		}
	}
}

void UDisplaySettingsHelper::PrintVirtualDisplayRect()
{
	if (GEngine)
	{
		FDisplayMetrics DisplayMetrics;

		FDisplayMetrics::RebuildDisplayMetrics(DisplayMetrics);

		UE_LOG(LogTemp, Log, TEXT("Left: %d"), DisplayMetrics.VirtualDisplayRect.Left);
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::White, FString::Printf(TEXT("Left = %d"), DisplayMetrics.VirtualDisplayRect.Left));
	}
}

void UDisplaySettingsHelper::PrintAllMonitorDisplayRects()
{
	if (GEngine)
	{
		FDisplayMetrics DisplayMetrics;

		FDisplayMetrics::RebuildDisplayMetrics(DisplayMetrics);
		
		for (int i = 0; i < DisplayMetrics.MonitorInfo.Num(); i++)
		{
			UE_LOG(LogTemp, Log, TEXT("Left: %d"), DisplayMetrics.MonitorInfo[i].DisplayRect.Left);
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::White, FString::Printf(TEXT("Left = %d"), DisplayMetrics.MonitorInfo[i].DisplayRect.Left));
		}
	}
}

void UDisplaySettingsHelper::PrintWindowScreenPosition()
{
	FVector2D WindowVec = FSlateApplication::Get().GetActiveTopLevelWindow()->GetPositionInScreen();

	UE_LOG(LogTemp, Log, TEXT("%i, %i"), (int)WindowVec.X, (int)WindowVec.Y);
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::White, FString::Printf(TEXT("%i, %i"), (int)WindowVec.X, (int)WindowVec.Y));
}
