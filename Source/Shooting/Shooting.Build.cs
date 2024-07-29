using UnrealBuildTool;

public class Shooting : ModuleRules
{
	public Shooting(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicIncludePaths.AddRange(new string[] { });
        PrivateIncludePaths.AddRange(new string[] { });
        PublicDependencyModuleNames.AddRange(new string[] { "Core" });
        PrivateDependencyModuleNames.AddRange(new string[] { "CoreUObject", "Engine", "Common", "ABUtils", "HittableObjects" });
        DynamicallyLoadedModuleNames.AddRange(new string[] { });
	}
}
