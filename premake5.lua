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
        "%{prj.name}/lib/spdlog/include"
    }

    filter "system:Windows"
        cppdialect "C++17"
        staticruntime "On"

        defines {
            "GE_PLATFORM_WINDOWS",
            "GE_BUILD_DLL"
        }

        pchsource "%{prj.name}/src/gepch.cpp"

    filter "configurations:Debug"
        defines { "GE_DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "GE_RELEASE" }
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
        symbols "On"

    filter "configurations:Release"
        defines { "GE_RELEASE" }
        optimize "On"