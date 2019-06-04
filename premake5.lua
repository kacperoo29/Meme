workspace "Meme"
	architecture "x64"

	configurations 
	{
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project "GLFW"
	location "Meme/3rdparty/GLFW"
	kind "StaticLib"
	language "C"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"Meme/3rdparty/GLFW/include/GLFW/glfw3.h",
        "Meme/3rdparty/GLFW/include/GLFW/glfw3native.h",
        "Meme/3rdparty/GLFW/src/glfw_config.h",
        "Meme/3rdparty/GLFW/src/context.c",
        "Meme/3rdparty/GLFW/src/init.c",
        "Meme/3rdparty/GLFW/src/input.c",
        "Meme/3rdparty/GLFW/src/monitor.c",
        "Meme/3rdparty/GLFW/src/vulkan.c",
        "Meme/3rdparty/GLFW/src/window.c"
	}
	
	filter "system:windows"
		buildoptions { "-std=c11", "-lgdi32" }
		systemversion "latest"
		staticruntime "On"
		files
        {
           "Meme/3rdparty/GLFW/src/win32_init.c",
           "Meme/3rdparty/GLFW/src/win32_joystick.c",
           "Meme/3rdparty/GLFW/src/win32_monitor.c",
           "Meme/3rdparty/GLFW/src/win32_time.c",
           "Meme/3rdparty/GLFW/src/win32_thread.c",
           "Meme/3rdparty/GLFW/src/win32_window.c",
           "Meme/3rdparty/GLFW/src/wgl_context.c",
           "Meme/3rdparty/GLFW/src/egl_context.c",
           "Meme/3rdparty/GLFW/src/osmesa_context.c"
        }
		
		defines 
		{ 
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
		}
		
	filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"
		

project "Meme"
	location "Meme"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "stdafx.h"
	pchsource "Meme/src/stdafx.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs 
	{
		"%{prj.name}/3rdparty/spdlog/include",
		"%{prj.name}/3rdparty/glfw/include",
		"Meme/src"
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

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/launcher")
		}

	filter "configurations:Debug"
		defines "__DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "__RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "__DIST"
		optimize "On"
		

project "Launcher"
	location "launcher"
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
		"Meme/3rdparty/spdlog/include",
		"Meme/src"
	}

	links
	{
		"Meme"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		defines "__DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "__RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "__DIST"
		optimize "On"