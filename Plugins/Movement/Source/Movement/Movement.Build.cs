// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Movement : ModuleRules
{
	public Movement(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string[] { });
		
		PrivateIncludePaths.AddRange(new string[] { } );
		
        PublicDependencyModuleNames.AddRange(new string[] { "Core" });

        PrivateDependencyModuleNames.AddRange(new string[] { "CoreUObject", "Engine", "Niagara" });

        DynamicallyLoadedModuleNames.AddRange(new string[] { });
	}
}
