using UnrealBuildTool;

public class UI : ModuleRules
{
    public UI(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicIncludePaths.AddRange(new string[] { });
        PrivateIncludePaths.AddRange(new string[] { });
        PublicDependencyModuleNames.AddRange(new string[] { "Core" });
        PrivateDependencyModuleNames.AddRange(new string[] { "CoreUObject", "Engine", "Common", "ABUtils", "Movement", "Shooting", "AGC", "Player" });
        DynamicallyLoadedModuleNames.AddRange(new string[] { });
    }
}