-- premake5.lua
project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. output_dir .. "/%{prj.name}")
    objdir ("%{wks.location}/int/" .. output_dir .. "/%{prj.name}")

    files {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs {
        "%{wks.location}/GamEngine/lib/spdlog/include",
        "%{wks.location}/GamEngine/src",
        "%{wks.location}/GamEngine/lib"
    }

    links { "GamEngine" }
    
    filter "system:Windows"

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