workspace "Meme"
	architecture "x64"

	configurations 
	{
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project "Meme"
	location "meme"
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
		"%{prj.name}/3rdparty/spdlog/include"
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
		"meme/3rdparty/spdlog/include",
		"meme/src"
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