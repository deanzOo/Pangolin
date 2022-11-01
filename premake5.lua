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
include_dir["ImGui"] = "GamEngine/lib/ImGui"

include "GamEngine/lib/GLFW"
include "GamEngine/lib/Glad"
include "GamEngine/lib/ImGui"

project "GamEngine"
    location "GamEngine"
    kind "SharedLib"
    language "C++"
    staticruntime "off"

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
        "%{include_dir.Glad}",
        "%{include_dir.ImGui}"
    }

    links {
        "GLFW",
        "GLAD",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:Windows"
        cppdialect "C++17"

        defines {
            "GE_PLATFORM_WINDOWS",
            "GE_BUILD_DLL"
        }

        pchsource "%{prj.name}/src/gepch.cpp"

    filter "configurations:Debug"
        defines { "GE_DEBUG", "GE_ENABLE_ASSERTS" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "GE_RELEASE" }
        runtime "Release"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"

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

        defines {
            "GE_PLATFORM_WINDOWS"
        }

        postbuildcommands { ("{COPY} %{wks.location}/bin/" .. output_dir .. "/GamEngine %{wks.location}/bin/" .. output_dir .. "/%{prj.name}") }

    filter "configurations:Debug"
        defines { "GE_DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "GE_RELEASE" }
        runtime "Release"
        optimize "On"