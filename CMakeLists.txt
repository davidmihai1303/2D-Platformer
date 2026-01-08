cmake_minimum_required(VERSION 3.22)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
# for now, the project name is used as the executable name
set(MAIN_PROJECT_NAME "SoundFugue")
set(MAIN_EXECUTABLE_NAME "${MAIN_PROJECT_NAME}")

project(${MAIN_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Options.cmake)
include(cmake/CompilerFlags.cmake)
include(cmake/CopyHelper.cmake)

###############################################################################
# 1. External Dependency: SFML 3 (FetchContent)
###############################################################################

include(FetchContent)

set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

set(SFML_WARNINGS_AS_ERRORS OFF)

# NOTE: Also update SFML_VERSION env var in .github/workflows/cmake.yml:33
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        # renovate: datasource=github-tags depName=SFML/SFML versioning=loose
        GIT_TAG        3.0.2

        GIT_SHALLOW    1
)

FetchContent_MakeAvailable(SFML)

###############################################################################
# 2. External Dependency: tmxlite (Local Source)
###############################################################################

# Define where the tmxlite external folder is
set(TMXLITE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/external/tmxlite")
set(TMXLITE_SRC_DIR "${TMXLITE_ROOT}/src")

# Combine the sources from the tmxlite CMake snippet you provided
set(TMXLITE_SOURCES
        ${TMXLITE_SRC_DIR}/FreeFuncs.cpp
        ${TMXLITE_SRC_DIR}/ImageLayer.cpp
        ${TMXLITE_SRC_DIR}/Map.cpp
        ${TMXLITE_SRC_DIR}/Object.cpp
        ${TMXLITE_SRC_DIR}/ObjectGroup.cpp
        ${TMXLITE_SRC_DIR}/Property.cpp
        ${TMXLITE_SRC_DIR}/TileLayer.cpp
        ${TMXLITE_SRC_DIR}/LayerGroup.cpp
        ${TMXLITE_SRC_DIR}/Tileset.cpp
        ${TMXLITE_SRC_DIR}/ObjectTypes.cpp
        # Lib sources (miniz, pugixml)
        ${TMXLITE_SRC_DIR}/miniz.c
        ${TMXLITE_SRC_DIR}/detail/pugixml.cpp
)

# Create the library target
add_library(tmxlite STATIC ${TMXLITE_SOURCES})

# Add the include directory so you can use #include <tmxlite/Map.hpp>
# This points to 'external/tmxlite', which contains the 'tmxlite' folder with headers.
target_include_directories(tmxlite PUBLIC "${TMXLITE_ROOT}")

# (Optional) Ensure tmxlite knows where its own internal headers are if needed,
# though usually relative paths in source handle this.
target_include_directories(tmxlite PRIVATE "${TMXLITE_SRC_DIR}")

###############################################################################
# System Dependencies
###############################################################################

find_package(Threads REQUIRED)
if(APPLE)
elseif(UNIX)
    find_package(X11)
endif()

###############################################################################
# Main Executable
###############################################################################

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing name here
add_executable(${MAIN_EXECUTABLE_NAME}
        src/main.cpp
        src/Player.cpp
        src/Player.hpp
        src/Game.cpp
        src/Game.hpp
        src/World.cpp
        src/World.hpp

        src/Enemy.cpp
        src/Enemy.hpp
        src/TextureHolder.cpp
        src/TextureHolder.hpp
        src/Entity.cpp
        src/Entity.hpp
        src/Note.cpp
        src/Note.hpp
        src/InputState.hpp
        src/Constants.hpp
)

# NOTE: Add all defined targets (e.g. executables, libraries, etc. )
# NOTE: RUN_SANITIZERS is optional, if it's not present it will default to true
set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_EXECUTABLE_NAME})

###############################################################################
# Linking and Include Configuration
###############################################################################

# use SYSTEM so cppcheck and clang-tidy do not report warnings from these directories
target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE ${SFML_SOURCE_DIR}/include)
target_link_directories(${MAIN_EXECUTABLE_NAME} PRIVATE ${SFML_BINARY_DIR}/lib)

# Link SFML and the new tmxlite library
target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
        Threads::Threads
        tmxlite
)

if(APPLE)
elseif(UNIX)
    target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE X11)
endif()

###############################################################################
# Installation / Copying
###############################################################################

# copy binaries to "bin" folder; these are uploaded as artifacts on each release
# DESTINATION_DIR is set as "bin" in cmake/Options.cmake:6
install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

copy_files(FILES tastatura.txt COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
# copy_files(FILES tastatura.txt config.json DIRECTORY images sounds COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
# copy_files(DIRECTORY images sounds COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})