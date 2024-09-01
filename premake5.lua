workspace "gcix"
    configurations { "Release", "Debug" }
    architecture "x86"
    location "."

project "gcix"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"
    targetdir "build/%{cfg.buildcfg}/"
    targetname "d3d9"
    objdir "build/intermediates/%{cfg.buildcfg}/"

    files { "src/**.h", "src/**.cpp" }
    files { "ext/minhook/**.h", "ext/minhook/**.c" }

    includedirs { "ext/minhook" }

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
        characterset "MBCS"
        runtime "Release"

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        characterset "MBCS"
        runtime "Debug"

newoption {
    trigger = "postbuildcopy",
    value = "path",
    description = "Optional parameter for post build operation to copy the DLL to a specific path"
}

if _OPTIONS["postbuildcopy"] then
    local saneCopyToPath = _OPTIONS["postbuildcopy"]:gsub("\\", "\\\\")

    postbuildcommands {
        -- Ensure the target directory exists
        "{MKDIR} " .. saneCopyToPath,
        -- Copy the DLL file
        "{COPY} %{cfg.buildtarget.abspath} " .. saneCopyToPath
    }
end
