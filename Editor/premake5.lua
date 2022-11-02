project ("Editor")
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"
    toolset "v143"

    targetdir ("%{wks.location}/bin/"..OutputDir.."/%{prj.name}")
    objdir ("%{wks.location}/bin-int/"..OutputDir.."/%{prj.name}")

    files
    {
        "Source/**.h",
        "Source/**.cpp",
    }

    includedirs {
        "%{wks.location}/Engine/Source"
    }

    links {
        "Engine"
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