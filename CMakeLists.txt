cmake_minimum_required(VERSION 3.16)
project(Vortex LANGUAGES C CXX ASM_NASM)

############################################################
## Include CMake files
include(${CMAKE_SOURCE_DIR}/Tools/CMake/binarySettings.cmake)
include(${CMAKE_SOURCE_DIR}/Tools/CMake/External/dependencies.cmake)
include(${CMAKE_SOURCE_DIR}/Tools/CMake/External/fetchContent.cmake)
include(${CMAKE_SOURCE_DIR}/Tools/CMake/External/sdlSettings.cmake)

############################################################
## General Environment Setup

# Set C++ standard
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build artifacts go to ./tmp/build_<preset>/ via CMake presets,
# Final binaries are placed in ./bin/ with appropriate naming
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Setup assembler
enable_language(ASM)

# Fix LTO-related toolchain issues if needed
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries for external deps" FORCE)
lto_fix()

# Prepare SDL settings
sdl_setup()

############################################################
## Setup Project
fetchContent()
setup_binary_settings()
configure_common_dependencies(Vortex)
target_include_directories(Vortex PUBLIC ${CMAKE_SOURCE_DIR}/include)


############################################################
## Platform-Specific

##################
# WINDOWS        #
##################
if(WIN32)
    message(STATUS "Targeting Windows")
    
    # Include Windows-specific configuration
    include(${CMAKE_SOURCE_DIR}/Tools/CMake/Platforms/windowsBuild.cmake)
    
    # Configure for Windows
    configure_windows(Vortex)

    # Prefer Win32 threads (avoid forcing pthread/winpthreads)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mthreads")
    set(CMAKE_THREAD_PREFER_PTHREAD FALSE)
    set(THREADS_PREFER_PTHREAD_FLAG FALSE)
    find_package(Threads REQUIRED)
##################
# APPLE          #
##################
elseif(APPLE)
    message(STATUS "Targeting macOS")
    
    # Include macOS-specific configuration
    include(${CMAKE_SOURCE_DIR}/Tools/CMake/Platforms/macosBuild.cmake)
    
    # Configure for macOS
    configure_macos(Vortex)
##################
# LINUX          #
##################
elseif(LINUX)
    message(STATUS "Targeting Linux")
    
    # Include Linux-specific configuration
    include(${CMAKE_SOURCE_DIR}/Tools/CMake/Platforms/linuxBuild.cmake)
    
    # Configure for Linux
    configure_linux(Vortex)
##################
# UNKNOWN        #
##################
else()
    message(FATAL_ERROR "Unsupported platform")
endif()