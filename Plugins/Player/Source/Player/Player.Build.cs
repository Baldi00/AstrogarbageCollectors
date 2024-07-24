// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Player : ModuleRules
{
	public Player(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] { });

        PrivateIncludePaths.AddRange(new string[] { });

        PublicDependencyModuleNames.AddRange(new string[] { "Core" });

        PrivateDependencyModuleNames.AddRange(new string[] { "CoreUObject", "Engine", "Movement", "Shooting", "EnhancedInput", "Niagara" });

        DynamicallyLoadedModuleNames.AddRange(new string[] { });
	}
}