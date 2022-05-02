// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;


public class Brunnhilde : ModuleRules
{
	public Brunnhilde(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[]
		{
			Path.Combine( ModuleDirectory, "Public/Characters"),
            Path.Combine( ModuleDirectory, "Public/Games"),
			Path.Combine( ModuleDirectory, "Public/Item"),
        });

		PublicDependencyModuleNames.AddRange(
			new string[]
		{ 
			"Core", 
			"CoreUObject",
			"Engine", 
			"InputCore",
			"HeadMountedDisplay" 
		});
	}
}
