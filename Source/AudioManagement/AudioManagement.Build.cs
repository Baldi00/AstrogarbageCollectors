using UnrealBuildTool;

public class AudioManagement : ModuleRules
{
    public AudioManagement(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicIncludePaths.AddRange(new string[] { });
        PrivateIncludePaths.AddRange(new string[] { });
        PublicDependencyModuleNames.AddRange(new string[] { "Core" });
        PrivateDependencyModuleNames.AddRange(new string[] { "CoreUObject", "Engine", "ABUtils", "Common", "Player", "Movement", "Shooting", "FMODStudio" });
        DynamicallyLoadedModuleNames.AddRange(new string[] { });
    }
}