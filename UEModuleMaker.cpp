#include <iostream>
#include <fstream>
#include <string>
#include <regex>

std::string BuildCsTemplate = "using UnrealBuildTool;\n\
\n\
public class #MODULE_NAME# : ModuleRules\n\
{\n\
    public #MODULE_NAME#(ReadOnlyTargetRules Target) : base(Target)\n\
    {\n\
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;\n\
        PublicIncludePaths.AddRange(new string[] { });\n\
        PrivateIncludePaths.AddRange(new string[] { });\n\
        PublicDependencyModuleNames.AddRange(new string[] { \"Core\" });\n\
        PrivateDependencyModuleNames.AddRange(new string[] { \"CoreUObject\", \"Engine\" });\n\
        DynamicallyLoadedModuleNames.AddRange(new string[] { });\n\
    }\n\
}";

std::string HeaderTemplate = "#pragma once\n\
\n\
#include \"CoreMinimal.h\"\n\
#include \"Modules/ModuleManager.h\"\n\
\n\
class F#MODULE_NAME#Module : public IModuleInterface\n\
{\n\
public:\n\
    virtual void StartupModule() override;\n\
    virtual void ShutdownModule() override;\n\
};";

std::string CppTemplate = "#include \"#MODULE_NAME#.h\"\n\
\n\
#define LOCTEXT_NAMESPACE \"F#MODULE_NAME#Module\"\n\
\n\
void F#MODULE_NAME#Module::StartupModule()\n\
{\n\
}\n\
\n\
void F#MODULE_NAME#Module::ShutdownModule()\n\
{\n\
}\n\
\n\
#undef LOCTEXT_NAMESPACE\n\
\n\
IMPLEMENT_MODULE(F#MODULE_NAME#Module, #MODULE_NAME#)";

int main()
{
    std::string ModuleName;
    std::cout << "Module name: ";
    std::cin >> ModuleName;

    system(std::string("mkdir " + ModuleName).c_str());
    system(std::string("mkdir " + ModuleName + "\\Public").c_str());
    system(std::string("mkdir " + ModuleName + "\\Private").c_str());

    std::string BuildCsContent = std::regex_replace(BuildCsTemplate, std::regex("#MODULE_NAME#"), ModuleName);
    std::string HeaderContent = std::regex_replace(HeaderTemplate, std::regex("#MODULE_NAME#"), ModuleName);
    std::string CppContent = std::regex_replace(CppTemplate, std::regex("#MODULE_NAME#"), ModuleName);

    std::string A(ModuleName + "\\" + ModuleName + ".Build.cs");
    std::string B(ModuleName + "\\Public\\" + ModuleName + ".h");
    std::string C(ModuleName + "\\Private\\" + ModuleName + ".cpp");

    std::ofstream BuildCsFile(ModuleName + "\\" + ModuleName + ".Build.cs");
    std::ofstream HeaderFile(ModuleName + "\\Public\\" + ModuleName + ".h");
    std::ofstream CppFile(ModuleName + "\\Private\\" + ModuleName + ".cpp");

    BuildCsFile << BuildCsContent;
    HeaderFile << HeaderContent;
    CppFile << CppContent;

    BuildCsFile.close();
    HeaderFile.close();
    CppFile.close();

    return 0;
}