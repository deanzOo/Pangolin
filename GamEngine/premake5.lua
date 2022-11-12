-- premake5.lua
project "GamEngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. output_dir .. "/%{prj.name}")
    objdir ("%{wks.location}/int/" .. output_dir .. "/%{prj.name}")

    pchheader "gepch.h"
    pchsource "src/gepch.cpp"

    files {
        "src/**.h",
        "src/**.cpp",
        "lib/glm/**.hpp",
        "lib/glm/**.inl",
        "lib/stb/**.h",
        "lib/stb/**.cpp"
    }

    defines {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs {
        "src",
        "%{include_dirs.spdlog}",
		"%{include_dirs.GLFW}",
		"%{include_dirs.Glad}",
		"%{include_dirs.ImGui}",
		"%{include_dirs.glm}",
		"%{include_dirs.stb}"
    }

    links {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:Windows"
        defines "GE_PLATFORM_WINDOWS"

    filter "configurations:Debug"
        defines { "GE_DEBUG", "GE_ENABLE_ASSERTS" }
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "GE_RELEASE"
        runtime "Release"
        optimize "on"