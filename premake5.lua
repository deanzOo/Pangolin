-- premake5.lua
workspace "GamEngine"
    architecture "x64"

    configurations {
        "Debug",
        "Release"
    }

    platforms { "Windows" }

    filter "system:Windows"
        systemversion "latest"

output_dir = "%{cfg.architecture}/%{cfg.buildcfg}/%{cfg.system}"

include_dir = {}
include_dir["GLFW"] = "GamEngine/lib/GLFW/include"
include_dir["Glad"] = "GamEngine/lib/Glad/include"

include "GamEngine/lib/GLFW"
include "GamEngine/lib/Glad"

project "GamEngine"
    location "GamEngine"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. output_dir .. "/%{prj.name}")
    objdir ("int/" .. output_dir .. "/%{prj.name}")

    pchheader "gepch.h"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/lib/spdlog/include",
        "%{include_dir.GLFW}",
        "%{include_dir.Glad}"
    }

    links {
        "GLFW",
        "GLAD",
        "opengl32.lib"
    }

    filter "system:Windows"
        cppdialect "C++17"
        staticruntime "On"

        defines {
            "GE_PLATFORM_WINDOWS",
            "GE_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        pchsource "%{prj.name}/src/gepch.cpp"

    filter "configurations:Debug"
        defines { "GE_DEBUG", "GE_ENABLE_ASSERTS" }
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines { "GE_RELEASE" }
        buildoptions "/MD"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. output_dir .. "/%{prj.name}")
    objdir ("int/" .. output_dir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "GamEngine/lib/spdlog/include",
        "GamEngine/src"
    }

    links { "GamEngine" }
    
    filter "system:Windows"
        cppdialect "C++17"
        staticruntime "On"

        defines {
            "GE_PLATFORM_WINDOWS"
        }

        postbuildcommands { ("{COPY} %{wks.location}/bin/" .. output_dir .. "/GamEngine %{wks.location}/bin/" .. output_dir .. "/%{prj.name}") }

    filter "configurations:Debug"
        defines { "GE_DEBUG" }
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines { "GE_RELEASE" }
        buildoptions "/MD"
        optimize "On"