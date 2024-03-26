// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BeaverRebuild : ModuleRules
{
	public BeaverRebuild(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","UMG", "Slate", "SlateCore", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        PublicIncludePaths.AddRange(new string[] { "BeaverRebuild\\Source\\BeaverRebuild\\Public", "BeaverRebuild\\Intermediate\\Build\\Win64\\UnrealEditor\\Inc\\BeaverRebuild\\UHT" });

        PrivateIncludePaths.AddRange(new string[] { "BeaverRebuild\\Source\\BeaverRebuild\\Private", "BeaverRebuild\\Intermediate\\Build\\Win64\\UnrealEditor\\Inc\\BeaverRebuild\\UHT" });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
