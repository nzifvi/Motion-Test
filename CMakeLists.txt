cmake_minimum_required(VERSION 3.23)
project(untitled9 CXX)

set(CMAKE_CXX_STANDARD 23)

# VCPKG TOOLCHAIN SETUP
set(CMAKE_TOOLCHAIN_FILE "C:/Users/benja/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake")

# --- PATH DEFINITIONS FOR CONFIGURATION & BUILD ---
# These paths fix configuration errors (raylib_DIR, raylib_INCLUDE_DIR)
set(raylib_DIR "C:/Users/benja/.vcpkg-clion/vcpkg/installed/x64-mingw-dynamic/share/raylib")
set(raylib_INCLUDE_DIR "C:/Users/benja/.vcpkg-clion/vcpkg/installed/x64-mingw-dynamic/include")
set(raylib_LIBRARY "C:/Users/benja/.vcpkg-clion/vcpkg/installed/x64-mingw-dynamic/lib/libraylib.dll.a")

# Path to the actual DLL files for the runtime copy command
set(RAYLIB_DLL_PATH "C:/Users/benja/.vcpkg-clion/vcpkg/installed/x64-mingw-dynamic/bin/libraylib.dll")
set(GLFW_DLL_PATH "C:/Users/benja/.vcpkg-clion/vcpkg/installed/x64-mingw-dynamic/bin/glfw3.dll")


# Add the include path for the compiler
include_directories(${raylib_INCLUDE_DIR})

# Add the link path for the linker
link_directories("C:/Users/benja/.vcpkg-clion/vcpkg/installed/x64-mingw-dynamic/lib")

# Find the Raylib package (Configuration must succeed here)
find_package(raylib CONFIG REQUIRED)

# =========================================================================

add_executable(untitled9 main.cpp
        Headers/KinematicHandler.cpp
        Headers/KinematicHandler.h
        Headers/Entity.cpp
        Headers/Entity.h
        Headers/EntityLoader.cpp
        Headers/EntityLoader.h)

# Link the executable with the explicit library file and required system dependencies.
target_link_libraries(untitled9
        PRIVATE
        ${raylib_LIBRARY}
        winmm
        gdi32
        opengl32
        kernel32
)

# *** CRITICAL RUNTIME FIX: AUTO-COPY ALL REQUIRED DLLs ***

# 1. Copy the main Raylib DLL
add_custom_command(
        TARGET untitled9 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${RAYLIB_DLL_PATH}"
        $<TARGET_FILE_DIR:untitled9>
        COMMENT "Copying required Raylib DLL (libraylib.dll)."
)

# 2. Copy the dependency DLL (glfw3.dll)
add_custom_command(
        TARGET untitled9 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${GLFW_DLL_PATH}"
        $<TARGET_FILE_DIR:untitled9>
        COMMENT "Copying required dependency DLL (glfw3.dll)."
)