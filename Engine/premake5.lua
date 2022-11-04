project ("Engine")
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"
    toolset "v143"

    targetdir ("%{wks.location}/bin/"..OutputDir.."/%{prj.name}")
    objdir ("%{wks.location}/bin-int/"..OutputDir.."/%{prj.name}")

    pchheader "pch.h"
    pchsource "Source/pch.cpp"
    
    files { 
        "Source/**.h",
        "Source/**.cpp",
        "Dependencies/ImGui/**.h",
        "Dependencies/ImGui/**.cpp"
    }

    includedirs {
        "Source"
    }

    defines {
        "_CRT_SECURE_NO_WARNINGS"    
    }

    links
    {
        "d3d11.lib",
        "d3dcompiler.lib"
    }

	filter "platforms:Win32"
		system "Windows"
		architecture "x32"
        systemversion "latest"

    filter "platforms:Win64"
    	system "Windows"
    	architecture "x64"
        systemversion "latest"

    filter "configurations:Debug"
        defines "DEBUG" 
		runtime "Debug"
        symbols "on"
        
    filter "configurations:Release"
        defines "RELEASE" 
        runtime "Release"
        optimize "on"