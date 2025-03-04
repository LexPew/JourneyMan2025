// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "GenericPlatform/GenericApplication.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Windows/WindowsApplication.h"
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
	static FText GetDisplayName(int DisplayID = 0);
	UFUNCTION(BlueprintCallable, Category = "Settings|Display")
	static TArray<FText> GetAllDisplayNames();
};
