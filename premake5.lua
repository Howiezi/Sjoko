workspace "Sjoko"
  architecture "x64"
  startproject "Sandbox"

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
IncludeDir["Glad"] = "Sjoko/vendor/Glad/include"
IncludeDir["ImGui"] = "Sjoko/vendor/imgui"

group "Dependencies"
  include "Sjoko/vendor/GLFW"
  include "Sjoko/vendor/Glad"
  include "Sjoko/vendor/imgui"

  group ""

project "Sjoko"
  location "Sjoko"
  kind "SharedLib"
  language "C++"
  staticruntime "off"

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
    "%{IncludeDir.GLFW}",
    "%{IncludeDir.Glad}",
    "%{IncludeDir.ImGui}"
  }

  links
  {
    "GLFW",
    "Glad",
    "ImGui",
    "opengl32.lib"
  }

  filter "system:windows"
    cppdialect "C++17"
	  systemversion "latest"

	  defines 
	  {
	    "SJ_PLATFORM_WINDOWS",
      "SJ_BUILD_DLL",
      "GLFW_INCLUDE_NONE"
	  }

	  postbuildcommands
	  {
	    ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
	  }

  filter "configurations:Debug"
    defines "SJ_DEBUG"
    runtime "Debug"
	  symbols "On"

  filter "configurations:Release"
    defines "SJ_RELEASE"
    runtime "Release"
	  optimize "On"

  filter "configurations:Dist"
    defines "SJ_DIST"
    runtime "Release"
	  optimize "On"

project "Sandbox"
  location "Sandbox"
  kind "ConsoleApp"
  language "C++"
  staticruntime "off"

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
	  systemversion "latest"

	  defines 
	  {
	    "SJ_PLATFORM_WINDOWS"
	  }

  filter "configurations:Debug"
    defines "SJ_DEBUG"
    runtime "Debug"
	  symbols "On"

  filter "configurations:Release"
    defines "SJ_RELEASE"
    runtime "Release"
	  optimize "On"

  filter "configurations:Dist"
    defines "SJ_DIST"
    runtime "Release"
	  optimize "On"