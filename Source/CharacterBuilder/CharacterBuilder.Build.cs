// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CharacterBuilder : ModuleRules
{
	public CharacterBuilder(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
			}
			);
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Engine",
			"Slate",
			"SlateCore",
			"EditorStyle",
			"UnrealEd",
			"Slate",
			"SlateCore",
			"EditorStyle",
			"UnrealEd",
			"AssetTools",
			"AssetRegistry",
			"ToolMenus",
			"EditorFramework",
			"WorkspaceMenuStructure",
			"PropertyEditor",
			"Persona",
			"AdvancedPreviewScene",
			"GameplayTags",
		});
	}
}
