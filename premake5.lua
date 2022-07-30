workspace "Sjoko"
  architecture "x64"

  configurations
  {
    "Debug",
	  "Release",
	  "Dist"
  }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Sjoko/vendor/GLFW/include"

include "Sjoko/vendor/GLFW"

project "Sjoko"
  location "Sjoko"
  kind "SharedLib"
  language "C++"

  targetdir ("bin/" .. outputdir .. "/%{prj.name}")
  objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

  pchheader "sjpch.h"
  pchsource "Sjoko/src/sjpch.cpp"

  files
  {
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp"
  }

  includedirs
  {
    "%{prj.name}/src",
    "%{prj.name}/vendor/spdlog/include;",
    "%{IncludeDir.GLFW}"
  }

  links
  {
    "GLFW",
    "opengl32.lib"
  }

  filter "system:windows"
    cppdialect "C++17"
	  staticruntime "On"
	  systemversion "latest"

	  defines 
	  {
	    "SJ_PLATFORM_WINDOWS",
	    "SJ_BUILD_DLL"
	  }

	  postbuildcommands
	  {
	    ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
	  }

  filter "configurations:Debug"
    defines "SJ_DEBUG"
    buildoptions "/MDd"
	  symbols "On"

  filter "configurations:Release"
    defines "SJ_RELEASE"
    buildoptions "/MD"
	  optimize "On"

  filter "configurations:Dist"
    defines "SJ_DIST"
    buildoptions "/MD"
	  optimize "On"

project "Sandbox"
  location "Sandbox"
  kind "ConsoleApp"
  language "C++"

  targetdir ("bin/" .. outputdir .. "/%{prj.name}")
  objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

  files
  {
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp"
  }

  includedirs
  {
    "Sjoko/vendor/spdlog/include;",
    "Sjoko/src"
  }

  links
  {
    "Sjoko"
  }

  filter "system:windows"
    cppdialect "C++17"
	  staticruntime "On"
	  systemversion "latest"

	  defines 
	  {
	    "SJ_PLATFORM_WINDOWS"
	  }

  filter "configurations:Debug"
    defines "SJ_DEBUG"
    buildoptions "/MDd"
	  symbols "On"

  filter "configurations:Release"
    defines "SJ_RELEASE"
    buildoptions "/MD"
	  optimize "On"

  filter "configurations:Dist"
    defines "SJ_DIST"
    buildoptions "/MD"
	  optimize "On"