// Copyright © Christophe Savard 2021

using UnrealBuildTool;
using System.Collections.Generic;

public class SimpleShooterEditorTarget : TargetRules
{
	public SimpleShooterEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "SimpleShooter" } );
	}
}
