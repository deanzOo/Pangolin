-- premake5.lua
workspace "Pangolin"
    architecture "x64"
    startproject "RolliePoly"

    configurations {
        "Debug",
        "Release"
    }

    flags {
        "MultiProcessorCompile"
    }

    platforms { "Windows" }

    filter "system:Windows"
        systemversion "latest"

output_dir = "%{cfg.architecture}/%{cfg.buildcfg}/%{cfg.system}"

include_dirs = {}
include_dirs["spdlog"]  = "%{wks.location}/Pangolin/lib/spdlog/include"
include_dirs["GLFW"]    = "%{wks.location}/Pangolin/lib/GLFW/include"
include_dirs["Glad"]    = "%{wks.location}/Pangolin/lib/Glad/include"
include_dirs["ImGui"]   = "%{wks.location}/Pangolin/lib/ImGui"
include_dirs["glm"]     = "%{wks.location}/Pangolin/lib/glm"
include_dirs["stb"]     = "%{wks.location}/Pangolin/lib/stb"

group "Dependencies"
    include "Pangolin/lib/GLFW"
    include "Pangolin/lib/Glad"
    include "Pangolin/lib/ImGui"
group ""

include "Pangolin"
include "RolliePoly"
include "Sandbox"
