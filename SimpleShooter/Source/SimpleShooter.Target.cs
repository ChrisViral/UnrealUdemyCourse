// Copyright © Christophe Savard 2021

using UnrealBuildTool;
using System.Collections.Generic;

public class SimpleShooterTarget : TargetRules
{
	public SimpleShooterTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "SimpleShooter" } );
	}
}
