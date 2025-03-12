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
	
public:
	UPROPERTY(config)
	int32 DisplayID;

	UFUNCTION(BlueprintCallable, Category = "Settings|Config|Display")
	int32 GetDisplayID() const;

	UFUNCTION(BlueprintCallable, Category = "Settings")
	static UAstroGameUserSettings* GetAstroGameUserSettings();
};
