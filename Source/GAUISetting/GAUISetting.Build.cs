// Copyright (C) 2024 owoDra

using UnrealBuildTool;

public class GAUISetting : ModuleRules
{
	public GAUISetting(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[]
            {
                ModuleDirectory,
                ModuleDirectory + "/GAUISetting",
            }
        );

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", "CoreUObject", "Engine",

                "Slate", "SlateCore", "UMG",

                "GSCore", "GUIExt",
            }
        );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "DeveloperSettings", "PropertyPath",
            }
        );
    }
}
