cmake_minimum_required(VERSION 3.27)
project(nowherefighters)

set(CMAKE_CXX_STANDARD 17)
set(RAYLIB_VERSION 4.5)
find_package(raylib ${RAYLIB_VERSION} REQUIRED) # QUIET or REQUIRED

add_executable(${PROJECT_NAME} main.cpp
        Engine/Entity.cpp
        Engine/Entity.h
        Engine/Vectors.cpp
        Engine/Vectors.h
        Engine/Sprite.cpp
        Engine/Sprite.h
        Engine/AnimatedSet.cpp
        Engine/AnimatedSet.h
        Engine/Room.cpp
        Engine/Room.h
        Game/Player.cpp
        Game/Player.h
        Game/Rooms.cpp
        Game/Rooms.h
        Engine/App.cpp
        Engine/App.h
        Game/Sprites.cpp
        Game/Sprites.h
        Game/NPC.cpp
        Game/NPC.h
        Engine/TileMap.cpp
        Engine/TileMap.h
        Game/TileMaps.cpp
        Game/TileMaps.h
        Engine/Mail.cpp
        Engine/Mail.h
        Engine/Exception.h
        Script/ScriptWrapper.cpp
        Script/angelscript/add_on/scriptbuilder/scriptbuilder.cpp
        Script/angelscript/add_on/scriptarray/scriptarray.cpp
        Script/angelscript/add_on/scriptstdstring/scriptstdstring.cpp
        Script/angelscript/add_on/scriptstdstring/scriptstdstring_utils.cpp
        Script/ScriptObjects.cpp)

option(BUILD_SHARED_LIBS "Build shared library" OFF)
option(AS_NO_EXCEPTIONS "Disable exception handling in script context" OFF)

if(MSVC)
    set(MSVC_COMPILE_FLAGS "/MP" CACHE STRING "Compiler flags to use with MSVC")
endif()

if(APPLE)
    option(BUILD_FRAMEWORK "Build Framework bundle for OSX" OFF)
endif()

file(READ Script/angelscript/include/angelscript.h ANGELSCRIPT_H)
string(REGEX MATCH "#define ANGELSCRIPT_VERSION_STRING \"([0-9]*).([0-9]*).([0-9]*)" ANGELSCRIPT_VERSION_REGEX ${ANGELSCRIPT_H})
set(ANGELSCRIPT_VERSION_MAJOR ${CMAKE_MATCH_1})
set(ANGELSCRIPT_VERSION_MINOR ${CMAKE_MATCH_2})
set(ANGELSCRIPT_VERSION_PATCH ${CMAKE_MATCH_3})
set(PROJECT_VERSION ${ANGELSCRIPT_VERSION_MAJOR}.${ANGELSCRIPT_VERSION_MINOR}.${ANGELSCRIPT_VERSION_PATCH})

set(ARCHFLAGS "${CMAKE_SYSTEM_PROCESSOR}")
if (APPLE AND NOT IOS)
    if (${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
        set(ARCHFLAGS "aarch64")
    endif ()
endif ()

message(STATUS "Configuring angelscript ${PROJECT_VERSION}")

find_package(Threads)

set(ANGELSCRIPT_HEADERS
        Script/angelscript/include/angelscript.h
        Script/angelscript/source/as_array.h
        Script/angelscript/source/as_builder.h
        Script/angelscript/source/as_bytecode.h
        Script/angelscript/source/as_callfunc.h
        Script/angelscript/source/as_compiler.h
        Script/angelscript/source/as_config.h
        Script/angelscript/source/as_configgroup.h
        Script/angelscript/source/as_context.h
        Script/angelscript/source/as_criticalsection.h
        Script/angelscript/source/as_datatype.h
        Script/angelscript/source/as_debug.h
        Script/angelscript/source/as_generic.h
        Script/angelscript/source/as_map.h
        Script/angelscript/source/as_memory.h
        Script/angelscript/source/as_module.h
        Script/angelscript/source/as_objecttype.h
        Script/angelscript/source/as_outputbuffer.h
        Script/angelscript/source/as_parser.h
        Script/angelscript/source/as_property.h
        Script/angelscript/source/as_restore.h
        Script/angelscript/source/as_scriptcode.h
        Script/angelscript/source/as_scriptengine.h
        Script/angelscript/source/as_scriptfunction.h
        Script/angelscript/source/as_scriptnode.h
        Script/angelscript/source/as_scriptobject.h
        Script/angelscript/source/as_string.h
        Script/angelscript/source/as_string_util.h
        Script/angelscript/source/as_texts.h
        Script/angelscript/source/as_thread.h
        Script/angelscript/source/as_tokendef.h
        Script/angelscript/source/as_tokenizer.h
        Script/angelscript/source/as_typeinfo.h
        Script/angelscript/source/as_variablescope.h
)

set(ANGELSCRIPT_SOURCE
        Script/angelscript/source/as_atomic.cpp
        Script/angelscript/source/as_builder.cpp
        Script/angelscript/source/as_bytecode.cpp
        Script/angelscript/source/as_callfunc.cpp
        Script/angelscript/source/as_callfunc_mips.cpp
        Script/angelscript/source/as_callfunc_x86.cpp
        Script/angelscript/source/as_callfunc_x64_gcc.cpp
        Script/angelscript/source/as_callfunc_x64_msvc.cpp
        Script/angelscript/source/as_callfunc_x64_mingw.cpp
        Script/angelscript/source/as_compiler.cpp
        Script/angelscript/source/as_configgroup.cpp
        Script/angelscript/source/as_context.cpp
        Script/angelscript/source/as_datatype.cpp
        Script/angelscript/source/as_gc.cpp
        Script/angelscript/source/as_generic.cpp
        Script/angelscript/source/as_globalproperty.cpp
        Script/angelscript/source/as_memory.cpp
        Script/angelscript/source/as_module.cpp
        Script/angelscript/source/as_objecttype.cpp
        Script/angelscript/source/as_outputbuffer.cpp
        Script/angelscript/source/as_parser.cpp
        Script/angelscript/source/as_restore.cpp
        Script/angelscript/source/as_scriptcode.cpp
        Script/angelscript/source/as_scriptengine.cpp
        Script/angelscript/source/as_scriptfunction.cpp
        Script/angelscript/source/as_scriptnode.cpp
        Script/angelscript/source/as_scriptobject.cpp
        Script/angelscript/source/as_string.cpp
        Script/angelscript/source/as_string_util.cpp
        Script/angelscript/source/as_thread.cpp
        Script/angelscript/source/as_tokenizer.cpp
        Script/angelscript/source/as_typeinfo.cpp
        Script/angelscript/source/as_variablescope.cpp
)

if(MSVC AND CMAKE_CL_64)
    enable_language(ASM_MASM)
    if(CMAKE_ASM_MASM_COMPILER_WORKS)
        set(ANGELSCRIPT_SOURCE ${ANGELSCRIPT_SOURCE} ../../source/as_callfunc_x64_msvc_asm.asm)
    else()
        message(FATAL ERROR "MSVC x86_64 target requires a working assembler")
    endif()
endif()

if(${ARCHFLAGS} MATCHES "^arm")
    enable_language(ASM)
    if(CMAKE_ASM_COMPILER_WORKS)
        set(ANGELSCRIPT_SOURCE ${ANGELSCRIPT_SOURCE} ../../source/as_callfunc_arm.cpp ../../source/as_callfunc_arm_gcc.S)
        set_property(SOURCE ../../source/as_callfunc_arm_gcc.S APPEND PROPERTY COMPILE_FLAGS " -Wa,-mimplicit-it=always")
    else()
        message(FATAL ERROR "ARM target requires a working assembler")
    endif()
endif()

if(${ARCHFLAGS} MATCHES "^aarch64")
    enable_language(ASM)
    if(CMAKE_ASM_COMPILER_WORKS)
        if(NOT APPLE)
            set(ANGELSCRIPT_SOURCE ${ANGELSCRIPT_SOURCE} ../../source/as_callfunc_arm64.cpp ../../source/as_callfunc_arm64_gcc.S)
        else()
            set(ANGELSCRIPT_SOURCE ${ANGELSCRIPT_SOURCE} ../../source/as_callfunc_arm64.cpp ../../source/as_callfunc_arm64_xcode.S
                    Engine/AngelMacros.h)
        endif()
    else()
        message(FATAL ERROR "ARM target requires a working assembler")
    endif()
endif()

if(MSVC)
    set(CMAKE_DEBUG_POSTFIX "d")
endif()

if(NOT BUILD_FRAMEWORK)
    set(ANGELSCRIPT_LIBRARY_NAME angelscript)
else()
    set(ANGELSCRIPT_LIBRARY_NAME Angelscript) # OS X frameworks should have capitalized name
    set(BUILD_SHARED_LIBS TRUE)
endif()
set(ANGELSCRIPT_LIBRARY_NAME ${ANGELSCRIPT_LIBRARY_NAME} CACHE STRING "" FORCE)

add_library(${ANGELSCRIPT_LIBRARY_NAME} ${ANGELSCRIPT_SOURCE} ${ANGELSCRIPT_HEADERS})

target_include_directories(${ANGELSCRIPT_LIBRARY_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>")

if(MSVC)
    target_compile_definitions(${ANGELSCRIPT_LIBRARY_NAME} PRIVATE -D_CRT_SECURE_NO_WARNINGS)
endif()

target_compile_definitions(${ANGELSCRIPT_LIBRARY_NAME} PRIVATE -DANGELSCRIPT_EXPORT -D_LIB)

if(AS_NO_EXCEPTIONS)
    target_compile_definitions(${ANGELSCRIPT_LIBRARY_NAME} PRIVATE AS_NO_EXCEPTIONS)
endif()

# Fix x64 issues on Linux
if("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64" AND UNIX AND NOT APPLE)
    target_compile_options(${ANGELSCRIPT_LIBRARY_NAME} PRIVATE -fPIC)
endif()

# Don't override the default library output path to avoid conflicts when building for multiple target platforms
#set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../lib)
target_link_libraries(${ANGELSCRIPT_LIBRARY_NAME} Threads::Threads)

set_target_properties(${ANGELSCRIPT_LIBRARY_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

if(BUILD_FRAMEWORK)
    set_target_properties(${ANGELSCRIPT_LIBRARY_NAME} PROPERTIES
            FRAMEWORK TRUE
            FRAMEWORK_VERSION ${PROJECT_VERSION}
            MACOSX_FRAMEWORK_IDENTIFIER com.angelcode.Angelscript
            MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${PROJECT_VERSION}
            MACOSX_FRAMEWORK_BUNDLE_VERSION ${PROJECT_VERSION}
            XCODE_ATTRIBUTE_INSTALL_PATH "@rpath"
            PUBLIC_HEADER ../../include/angelscript.h
    )
endif()

if(MSVC AND MSVC_COMPILE_FLAGS)
    target_compile_options(${ANGELSCRIPT_LIBRARY_NAME} PRIVATE "${MSVC_COMPILE_FLAGS}")
endif()

# Don't override the default runtime output path to avoid conflicts when building for multiple target platforms
#set(RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../bin)

#See https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html#creating-packages for a detailed explanation about this part
install(TARGETS ${ANGELSCRIPT_LIBRARY_NAME} EXPORT AngelscriptTargets
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        INCLUDES DESTINATION include
)

install(FILES
        ${CMAKE_CURRENT_SOURCE_DIR}Script/angelscript/angelscript.h
        DESTINATION include
        COMPONENT Devel
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/Angelscript/AngelscriptConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
)

export(EXPORT AngelscriptTargets
        FILE "${CMAKE_CURRENT_BINARY_DIR}/Angelscript/AngelscriptTargets.cmake"
        NAMESPACE Angelscript::
)
configure_file(cmake/AngelscriptConfig.cmake
        "${CMAKE_CURRENT_BINARY_DIR}/Angelscript/AngelscriptConfig.cmake"
        COPYONLY
)

set(ConfigPackageLocation lib/cmake/Angelscript)
install(EXPORT AngelscriptTargets
        FILE AngelscriptTargets.cmake
        NAMESPACE Angelscript::
        DESTINATION ${ConfigPackageLocation}
)
install(
        FILES
        cmake/AngelscriptConfig.cmake
        "${CMAKE_CURRENT_BINARY_DIR}/Angelscript/AngelscriptConfigVersion.cmake"
        DESTINATION ${ConfigPackageLocation}
        COMPONENT Devel
)

target_link_libraries(${PROJECT_NAME} raylib angelscript)