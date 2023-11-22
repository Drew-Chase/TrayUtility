local name = path.getbasename(os.getcwd())
local directory = os.getcwd()

-- Create directories
os.execute("mv \"" .. directory .. "/project" .. "\" \"" .. directory .. "/" .. name .. "\"")
os.execute("mkdir \"" .. name .. "\"")
os.execute("mkdir \"" .. directory .. "/" .. name .. "/includes\"")
os.execute("mkdir \"" .. directory .. "/" .. name .. "/src\"")
os.execute("mkdir vendor")


workspace (name)
    configurations { "Example", "Dynamic Library", "Static Library Debug", "Static Library" }
    platforms { "Win32", "x64" }

project (name)
    location (name)
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    cdialect "C17"
    characterset "Unicode"
    
    filter "configurations:Example"
        kind "StaticLib"
        defines { "STATIC_LIBRARY_DEBUG" }
        symbols "On"
        targetextension "-d.lib"
        targetdir "bin/build/lib"
        staticruntime "On"
        objdir "bin/obj/lib-d"

    filter "configurations:Dynamic Library"
        kind "SharedLib"
        defines { "DYNAMIC_LIBRARY" }
        targetdir "bin/build/bin"
        staticruntime "Off"
        objdir "bin/obj/dll"
        
    filter "configurations:Static Library Debug"
        kind "StaticLib"
        defines { "STATIC_LIBRARY_DEBUG" }
        symbols "On"
        targetextension "-d.lib"
        targetdir "bin/build/lib"
        staticruntime "On"
        objdir "bin/obj/lib-d"
        
    filter "configurations:Static Library"
        kind "StaticLib"
        defines { "STATIC_LIBRARY" }
        staticruntime "On"
        targetextension ".lib"
        targetdir "bin/build/lib"
        objdir "bin/obj/lib"

    filter "platforms:Win32"
        architecture "x86"

    filter "platforms:x64"
        architecture "x86_64"

    filter {} -- reset filter

    includedirs { name .. "/includes", "include" } -- Add "include" directory
    files { name .. "/**/*.rc", name .. "/**/*.h", name .. "/**/*.cpp", "**/src/**.h", "**/src/**.cpp" } -- Add "src" directory

project "example"
    location "example"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    cdialect "C17"
    links { name }

    characterset "Unicode"
    filter "configurations:Example"
        defines { "EXAMPLE" }
        targetdir "bin/Example/"
        objdir "bin/obj/example"
        staticruntime "Off"

    filter "configurations:Dynamic Library"
        kind "SharedLib"
        defines { "DYNAMIC_LIBRARY" }
        targetdir "bin/build/bin"
        staticruntime "Off"
        objdir "bin/obj/dll"
        
    filter "configurations:Static Library Debug"
        kind "StaticLib"
        defines { "STATIC_LIBRARY_DEBUG" }
        symbols "On"
        targetextension "-d.lib"
        targetdir "bin/build/lib"
        staticruntime "On"
        objdir "bin/obj/lib-d"
        
    filter "configurations:Static Library"
        kind "StaticLib"
        defines { "STATIC_LIBRARY" }
        staticruntime "On"
        targetextension ".lib"
        targetdir "bin/build/lib"
        objdir "bin/obj/lib"

    filter "platforms:Win32"
        architecture "x86"

    filter "platforms:x64"
        architecture "x86_64"
        
    filter {} -- reset filter
    files { "example/main.cpp" }
    includedirs { name .. "/includes", "include" } -- Add "include" directory