// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class JourneyManTarget : TargetRules
{
	public JourneyManTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
//Testing updated 
		ExtraModuleNames.AddRange( new string[] { "JourneyMan" } );
	}
}
