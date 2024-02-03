// Copyright (C) 2024 owoDra

using UnrealBuildTool;

public class GAUISettingEditor : ModuleRules
{
	public GAUISettingEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;	

		PublicIncludePaths.AddRange(
            new string[] 
			{
                ModuleDirectory,
                ModuleDirectory + "/GAUISettingEditor",
            }
        );			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
			}
		);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "Core", "CoreUObject", "Engine",

                "UnrealEd", "Slate", "SlateCore", "UMG",

                "DeveloperSettings", "PropertyPath", "PropertyEditor",

                "ToolWidgets", "ClassViewer", "AssetTools",

                "GAUISetting",
            }
		);
	}
}
