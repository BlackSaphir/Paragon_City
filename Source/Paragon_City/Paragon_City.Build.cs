// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Paragon_City : ModuleRules
{
    public Paragon_City(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "ProceduralMeshComponent" });
        PrivateDependencyModuleNames.AddRange(new string[] {
                "CoreUObject",
                "Slate",
                "SlateCore",
                "RHI",
                "Renderer",
                "RenderCore",
                "ShaderCore",
                "HeadMountedDisplay",
                "IOSRuntimeSettings",
                "AugmentedReality",
                "ProceduralMeshComponent",
                "LiveLink",
                "LiveLinkInterface",
//                "OnlineSubsystem",
                "Sockets"
				// ... add private dependencies that you statically link with here ...
			}
            );
        PublicIncludePaths.AddRange(new string[] { "AppleARKit/Public" });
        PrivateIncludePaths.AddRange(new string[] { "AppleARKit/Private", "../../../../Source/Runtime/Renderer/Private", });

        if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            PublicDefinitions.Add("ARKIT_SUPPORT=1");
            PublicFrameworks.Add("ARKit");
        }
        else
        {
            PublicDefinitions.Add("ARKIT_SUPPORT=0");
        }

    }
}
