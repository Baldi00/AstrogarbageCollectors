using UnrealBuildTool;

public class AGC : ModuleRules
{
    public AGC(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "ABUtils",
            "Player",
            "HittableObjects",
            "Common",
            "NetCore",
            "Sockets",
            "OnlineSubsystem",
            "OnlineSubsystemUtils",
            "UMG"
        });
        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
