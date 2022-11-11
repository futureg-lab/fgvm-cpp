project "fgvm-examples"
	kind "StaticLib"
	language "C++"

	targetdir "%{wks.location}/bin/%{cfg.buildcfg}/%{prj.name}"
	objdir "%{wks.location}/obj/%{cfg.buildcfg}/%{prj.name}"
	
	files {
		"**.h",
		"**.hpp",
		"**.cpp"
	}

   -- filters
	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "On"

	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "On"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

   filter "configurations:Release"
		runtime "Release"
		optimize "on"