-- premake5.lua
project "RolliePoly"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. output_dir .. "/%{prj.name}")
    objdir ("%{wks.location}/int/" .. output_dir .. "/%{prj.name}")

    files {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs {
        "%{wks.location}/Pangolin/lib/spdlog/include",
        "%{wks.location}/Pangolin/src",
        "%{wks.location}/Pangolin/lib",
		"%{include_dirs.glm}"
    }

    links { "Pangolin" }
    
    filter "system:Windows"
        defines "GE_PLATFORM_WINDOWS"

    filter "configurations:Debug"
        defines "GE_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "GE_RELEASE"
        runtime "Release"
        optimize "On"