-- premake5.lua
workspace "GamEngine"
    architecture "x64"
    startproject "Sandbox"

    configurations {
        "Debug",
        "Release"
    }

    platforms { "Windows" }

    filter "system:Windows"
        systemversion "latest"

output_dir = "%{cfg.architecture}/%{cfg.buildcfg}/%{cfg.system}"

include_dirs = {}
include_dirs["spdlog"]  = "%{wks.location}/GamEngine/lib/spdlog/include"
include_dirs["GLFW"]    = "%{wks.location}/GamEngine/lib/GLFW/include"
include_dirs["Glad"]    = "%{wks.location}/GamEngine/lib/Glad/include"
include_dirs["ImGui"]   = "%{wks.location}/GamEngine/lib/ImGui"
include_dirs["glm"]     = "%{wks.location}/GamEngine/lib/glm"
include_dirs["stb"]     = "%{wks.location}/GamEngine/lib/stb"

include "GamEngine"
include "Sandbox"
include "GamEngine/lib/GLFW"
include "GamEngine/lib/Glad"
include "GamEngine/lib/ImGui"