// Copyright © Christophe Savard 2021

using UnrealBuildTool;

public class SimpleShooterEditorTarget : TargetRules
{
	public SimpleShooterEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("SimpleShooter");
	}
}
