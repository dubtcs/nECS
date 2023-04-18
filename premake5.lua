
    project "nECS"
        location "nECS";
        kind "StaticLib";
        language "C++";
        cppdialect "C++20";
        staticruntime "on";

        targetdir ("bin/"..output.."/%{prj.name}");
        objdir ("bin-int/"..output.."/%{prj.name}");

        files {
            "%{prj.name}/necs/**.h",
            "%{prj.name}/necs/**.cpp",
            "%{prj.name}/example.cpp",
        };

        includedirs {
            "%{prj.name}/necs",
        }

        filter "system:windows"
            systemversion "latest";
            filter "configurations:Debug"
            defines {}
            runtime "Debug"
            symbols "On"
    
        filter "configurations:Release"
            defines {}
            runtime "Release"
            optimize "On"
    
        filter "configurations:Dist"
            defines {}
            runtime "Release"
            optimize "On"