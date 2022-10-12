workspace ("Engine")
    startproject "Sandbox"

    configurations {
        "Debug",
        "Release"
    }

    platforms {
    	"Win32",
    	"Win64"
    }

    flags {
        "MultiProcessorCompile"
    }


OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" 

--DependencyDir = "%{ProjectName}/Dependencies"
--SourceDir = "%{ProjectName}/Source"

DependenciesDir = {}

include "Engine"
include "Sandbox"