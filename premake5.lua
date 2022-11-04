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
include_dirs["GLFW"] = "%{wks.locations}/GamEngine/lib/GLFW/include"
include_dirs["Glad"] = "%{wks.locations}/GamEngine/lib/Glad/include"
include_dirs["ImGui"] = "%{wks.locations}/GamEngine/lib/ImGui"
include_dirs["glm"] = "%{wks.locations}/GamEngine/lib/glm"

include "GamEngine"
include "Sandbox"
include "GamEngine/lib/GLFW"
include "GamEngine/lib/Glad"
include "GamEngine/lib/ImGui"