ProjectName = "GameEngine"

workspace (ProjectName)
    configurations 
    {
        "Debug",
        "Release"
    }

    platforms
    {
    	"Win32",
    	"Win64"
    } 


OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" 

DependencyDir = "%{ProjectName}/Dependencies"
SourceDir = "%{ProjectName}/Source"

-- Dependency Directiories --
DependenciesDir = {}
--DependenciesDir["GLFW"] = "%{DependencyDir}/GLFW"
--DependenciesDir["GLEW"] = "%{DependencyDir}/GLEW"
--DependenciesDir["GLM"] = "%{DependencyDir}/GLM"
--DependenciesDir["ImGui"] = "%{DependencyDir}/ImGui"
--DependenciesDir["Stb_image"] = "%{DependencyDir}/Stb_image"

project (ProjectName)
    location (ProjectName)
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"
    toolset "v143"

    
    targetdir ("bin/"..OutputDir.."/%{prj.name}")
    objdir ("bin-int/"..OutputDir.."/%{prj.name}")
    
    files
    {
        "%{SourceDir}/**.h",
        "%{SourceDir}/**.cpp",
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

		includedirs
	    {
            "%{SourceDir}"
	    }

	    libdirs
	    {
	    }

        defines
        {
            --"WIN32"
        }

    filter "platforms:Win64"
    	system "Windows"
    	architecture "x64"
        systemversion "latest"

		includedirs
	    {
            "%{SourceDir}"
            --"%{DependenciesDir.GLFW}/Win64/include",
            --"%{DependenciesDir.GLEW}/include",
            --"%{DependenciesDir.ImGui}",
            --"%{DependenciesDir.GLM}",
            --"%{DependenciesDir.Stb_image}"
	    }

	    libdirs
	    {
            --"%{DependenciesDir.GLFW}/Win64/lib",
            --"%{DependenciesDir.GLEW}/lib/Win64"
	    }

        defines
        {
            --"WIN64"
        }

    filter "configurations:Debug"
        defines "DEBUG" 
		runtime "Debug"
        symbols "on"
        
    filter "configurations:Release"
        defines "RELEASE" 
        runtime "Release"
        optimize "on"