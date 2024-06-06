workspace "gcix"
    configurations { "Release" }
    architecture "x86"
    location "build"

project "d3d9"
    kind "SharedLib"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
    targetname "d3d9"
    files { "src/**.h", "src/**.cpp" }
    
    includedirs { "ext/minhook/include" }
    
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
        characterset "MBCS"
        runtime "Release"

newoption {
    trigger = "postbuildcopy",
    value = "path",
    description = "Optional parameter for post build operation to copy the dll to a specific path"
}

if _OPTIONS["postbuildcopy"] then
    postbuildcommands {
        "{COPY} %{cfg.targetdir}/d3d9.dll " .. _OPTIONS["postbuildcopy"]
    }
end