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
IncludeDir["glm"] = "Sjoko/vendor/glm"
IncludeDir["stb_image"] = "Sjoko/vendor/stb_image"

group "Dependencies"
  include "Sjoko/vendor/GLFW"
  include "Sjoko/vendor/Glad"
  include "Sjoko/vendor/imgui"

  group ""

project "Sjoko"
  location "Sjoko"
  kind "StaticLib"
  language "C++"
  cppdialect "C++17"
  staticruntime "on"

  targetdir ("bin/" .. outputdir .. "/%{prj.name}")
  objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

  pchheader "sjpch.h"
  pchsource "Sjoko/src/sjpch.cpp"

  files
  {
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp",
    "%{prj.name}/vendor/stb_image/**.h",
    "%{prj.name}/vendor/stb_image/**.cpp",
    "%{prj.name}/vendor/glm/glm/**.hpp",
    "%{prj.name}/vendor/glm/glm/**.inl"
  }

  includedirs
  {
    "%{prj.name}/src",
    "%{prj.name}/vendor/spdlog/include;",
    "%{IncludeDir.GLFW}",
    "%{IncludeDir.Glad}",
    "%{IncludeDir.ImGui}",
    "%{IncludeDir.glm}",
    "%{IncludeDir.stb_image}"
  }

  links
  {
    "GLFW",
    "Glad",
    "ImGui",
    "opengl32.lib"
  }

  filter "system:windows"
	  systemversion "latest"

	  defines 
	  {
	    "SJ_PLATFORM_WINDOWS",
      "SJ_BUILD_DLL",
      "GLFW_INCLUDE_NONE"
    }
    
  filter "configurations:Debug"
    defines "SJ_DEBUG"
    runtime "Debug"
	  symbols "on"

  filter "configurations:Release"
    defines "SJ_RELEASE"
    runtime "Release"
	  optimize "on"

  filter "configurations:Dist"
    defines "SJ_DIST"
    runtime "Release"
	  optimize "on"

project "Sandbox"
  location "Sandbox"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++17"
  staticruntime "on"

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
    "Sjoko/src",
    "%{IncludeDir.glm}"
  }

  links
  {
    "Sjoko"
  }

  filter "system:windows"
	  systemversion "latest"

	  defines 
	  {
	    "SJ_PLATFORM_WINDOWS"
	  }

  filter "configurations:Debug"
    defines "SJ_DEBUG"
    runtime "Debug"
	  symbols "on"

  filter "configurations:Release"
    defines "SJ_RELEASE"
    runtime "Release"
	  optimize "on"

  filter "configurations:Dist"
    defines "SJ_DIST"
    runtime "Release"
	  optimize "on"