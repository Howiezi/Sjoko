workspace "Sjoko"
  architecture "x64"

  configurations
  {
    "Debug",
	  "Release",
	  "Dist"
  }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Sjoko"
  location "Sjoko"
  kind "SharedLib"
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
    "%{prj.name}/vendor/spdlog/include;"
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
	  symbols "On"

  filter "configurations:Release"
    defines "SJ_RELEASE"
	  optimize "On"

  filter "configurations:Dist"
    defines "SJ_DIST"
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
	  symbols "On"

  filter "configurations:Release"
    defines "SJ_RELEASE"
	  optimize "On"

  filter "configurations:Dist"
    defines "SJ_DIST"
	  optimize "On"