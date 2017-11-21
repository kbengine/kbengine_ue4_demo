// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class kbengine_ue4_demoEditorTarget : TargetRules
{
	public kbengine_ue4_demoEditorTarget(TargetInfo Target): base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("kbengine_ue4_demo");
	}
}
