project "Glad"
	kind "StaticLib"
	language "C"

	targetdir ("bin/" .. output_dir .. "/%{prj.name}")
	objdir ("int/" .. output_dir .. "/%{prj.name}")

	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
	}

	includedirs{
		"include"
	}
	
	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		buildoptions "/MT"
		optimize "on"