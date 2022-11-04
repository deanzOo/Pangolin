-- premake5.lua
project "GamEngine"
    kind "SharedLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. output_dir .. "/%{prj.name}")
    objdir ("%{wks.location}/int/" .. output_dir .. "/%{prj.name}")

    pchheader "gepch.h"
    pchsource "src/gepch.cpp"

    files {
        "src/**.h",
        "src/**.cpp",
        "lib/glm/glm/**.hpp",
        "lib/glm/glm/**.inl"
    }

    includedirs {
        "src",
        "lib/spdlog/include",
        "lib/GLFW/include",
        "lib/Glad/include",
        "lib/ImGui",
        "lib/glm"
    }

    links {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:Windows"
        defines { "GE_PLATFORM_WINDOWS", "GE_BUILD_DLL" }


    filter "configurations:Debug"
        defines { "GE_DEBUG", "GE_ENABLE_ASSERTS" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "GE_RELEASE" }
        runtime "Release"
        optimize "On"