// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Paragon_City : ModuleRules
{
    public Paragon_City(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay",  "AugmentedReality", });

        PublicIncludePaths.AddRange(new string[] { "AppleARKit/Public", "AppleARKit/Classes" });

        PrivateIncludePaths.AddRange(new string[] { "AppleARKit/Private", "AppleARKit/Classes", "GoogleARCoreBase/Private" });



        PrivateDependencyModuleNames.AddRange(new string[] 
        {
                "CoreUObject",
                "Slate",
                "SlateCore",
                "RHI",
                "Renderer",
                "RenderCore",
                "ShaderCore",
                "HeadMountedDisplay",
               
                "AugmentedReality",
                "ProceduralMeshComponent",
                "LiveLink",
                "LiveLinkInterface",
                 "OnlineSubsystem",
                "Sockets",
               
				// ... add private dependencies that you statically link with here ...
		}
        );
        
        

           

        if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            PublicDefinitions.Add("ARKIT_SUPPORT=1");
            PublicFrameworks.Add("ARKit");
            PublicDependencyModuleNames.AddRange(new string[] { "AppleARKit", });
            PrivateDependencyModuleNames.AddRange(new string[]
            {
                 "IOSRuntimeSettings",
                "AppleARKit",
            });
        }
        else
        {
            PublicDefinitions.Add("ARKIT_SUPPORT=0");
        }


        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            // Additional dependencies on android...
            PrivateDependencyModuleNames.Add("Launch");

            // Register Plugin Language
            AdditionalPropertiesForReceipt.Add("AndroidPlugin",/* Path.Combine(ModuleDirectory,*/ "GoogleARCoreBase_APL.xml");

            PrivateDependencyModuleNames.AddRange(new string[]
            { "AndroidPermission",
                "GoogleARCoreRendering",
                "GoogleARCoreSDK",
                "OpenGL",
                "UElibPNG",
                "zlib"
            });

            if (AndroidExports.CreateToolChain(Target.ProjectFile).GetNdkApiLevelInt(19) >= 24)
            {
                // Camera CPU image access dependency.
                PublicAdditionalLibraries.Add("mediandk");
            }
        }
    }
}
