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
		
project "glad"
	location "Meme/3rdparty/glad"
	kind "StaticLib"
	language "C"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"Meme/3rdparty/glad/include/glad/glad.h",
		"Meme/3rdparty/glad/include/KHR/khrplatform.h",
		"Meme/3rdparty/glad/src/glad.c"		
	}
	
	includedirs
	{
		"Meme/3rdparty/glad/include"
	}
		
	filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
		
project "imgui"
    kind "StaticLib"
	location "Meme/3rdparty/imgui"
    language "C++"
    
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
        "Meme/3rdparty/imgui/imconfig.h",
        "Meme/3rdparty/imgui/imgui.h",
        "Meme/3rdparty/imgui/imgui.cpp",
        "Meme/3rdparty/imgui/imgui_draw.cpp",
        "Meme/3rdparty/imgui/imgui_internal.h",
        "Meme/3rdparty/imgui/imgui_widgets.cpp",
        "Meme/3rdparty/imgui/imstb_rectpack.h",
        "Meme/3rdparty/imgui/imstb_textedit.h",
        "Meme/3rdparty/imgui/imstb_truetype.h",
        "Meme/3rdparty/imgui/imgui_demo.cpp"
    }
    
	filter "system:windows"
        systemversion "latest"
        cppdialect "C++17"
        staticruntime "On"
        
    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"		
		
project "Meme"
	location "Meme"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "stdafx.h"
	pchsource "Meme/src/stdafx.cpp"

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs 
	{
		"%{prj.name}/3rdparty/spdlog/include",
		"%{prj.name}/3rdparty/GLFW/include",
		"%{prj.name}/3rdparty/glad/include",
		"%{prj.name}/3rdparty/imgui",
		"%{prj.name}/3rdparty/glm",
		"%{prj.name}/src"
	}

	links
	{
		"GLFW",
		"glad",
		"imgui",
		"opengl32.lib"
	}

	filter "system:windows"				
		systemversion "latest"

		defines
		{
			"GLFW_INCLUDE_NONE",			
			"_GLFW_USE_DWM_SWAP_INTERVAL=1"
		}

	filter "configurations:Debug"
		defines "__DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "__RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "__DIST"
		runtime "Release"
		optimize "on"
		

project "Launcher"
	location "launcher"
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
		"Meme/3rdparty/spdlog/include",
		"Meme/3rdparty/imgui",
		"Meme/3rdparty/glm",
		"Meme/src"
	}

	links
	{
		"Meme"
	}

	filter "system:windows"
		cppdialect "C++17"		
		systemversion "latest"

	filter "configurations:Debug"
		defines "__DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "__RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "__DIST"
		runtime "Release"
		optimize "on"
		
