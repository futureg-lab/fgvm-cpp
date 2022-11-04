workspace "fgvm-project"
   configurations { "Debug", "Release" }

group "Lib"
   include "includes/fgvm/core"
   include "includes/fgvm/examples"
group ""

-- MAIN PROJECT HERE
project "sandbox"
   kind "ConsoleApp"
   language "C++"
   staticruntime "off"

   targetdir "%{wks.location}/bin/%{cfg.buildcfg}/%{prj.name}"
   objdir "%{wks.location}/obj/%{cfg.buildcfg}/%{prj.name}"

   includedirs { "includes" }

	files {
      "sandbox/**.hpp",
      "sandbox/**.cpp",
	}

   links { "fgvm-core", "fgvm-examples" }

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
        defines { "DEBUG" }
        symbols "On"

   filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"