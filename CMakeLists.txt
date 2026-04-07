cmake_minimum_required(VERSION 3.27)
# Specify the languages used to optimize configuration
project(Arcade LANGUAGES CXX)

# --- GLOBAL CONFIGURATION ---
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- DEPENDENCIES ---
include(FetchContent)

# Option to force SDL as a shared library
set(SDL_SHARED ON CACHE BOOL "Build SDL shared library" FORCE)
set(SDL_STATIC OFF CACHE BOOL "Build SDL static library" FORCE)

# Try to find SDL2 libraries
find_package(SDL2 QUIET)
find_package(SDL2_image QUIET)
find_package(SDL2_ttf QUIET)

# Fetch SDL2 libraries
if(NOT SDL2_FOUND AND NOT SDL2_image_FOUND AND NOT SDL2_ttf_FOUND)
    message(STATUS "Fetching SDL2 dependencies from GitHub...")
    FetchContent_Declare(SDL2 GIT_REPOSITORY https://github.com/libsdl-org/SDL.git GIT_TAG release-2.30.0 GIT_SHALLOW TRUE)
    FetchContent_Declare(SDL2_image GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git GIT_TAG release-2.8.2 GIT_SHALLOW TRUE)
    FetchContent_Declare(SDL2_ttf GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git GIT_TAG release-2.22.0 GIT_SHALLOW TRUE)

    # MakeAvailable can take multiple arguments at once
    FetchContent_MakeAvailable(SDL2 SDL2_image SDL2_ttf)
endif()

# --- INTERFACE TARGET ---
add_library(arcadeGlobal INTERFACE)

target_compile_options(arcadeGlobal INTERFACE
    -Wall -Wextra -Werror -Wpedantic
)

target_include_directories(arcadeGlobal INTERFACE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/interface
    ${PROJECT_SOURCE_DIR}/include/core
    ${PROJECT_SOURCE_DIR}/include/module
    ${PROJECT_SOURCE_DIR}/include/module/game
    ${PROJECT_SOURCE_DIR}/include/module/graphic
    ${PROJECT_SOURCE_DIR}/include/module/menu
)

# --- PROJECT CORE ---
file(GLOB CORE_FILES CONFIGURE_DEPENDS "source/core/*.cpp")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
add_executable(arcade source/main.cpp ${CORE_FILES})
target_link_libraries(arcade PRIVATE arcadeGlobal ${CMAKE_DL_LIBS})

# --- GAME MODULES ---
# --- MENU ---
add_library(ArcadeMenu SHARED
    source/module/menu/ArcadeMenu.cpp
    source/module/AGameModule.cpp
)

target_link_libraries(ArcadeMenu PRIVATE arcadeGlobal)

set_target_properties(ArcadeMenu PROPERTIES
    PREFIX ""
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib
)

# --- SNAKE ---
add_library(snake SHARED
    source/module/game/SnakeGame.cpp
    source/module/AGameModule.cpp
)

target_link_libraries(snake PRIVATE arcadeGlobal)

set_target_properties(snake PROPERTIES
    PREFIX "arcade_"
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib
)

# --- SOLARFOX ---
add_library(solarfox SHARED
    source/module/game/SolarfoxGame.cpp
    source/module/AGameModule.cpp
)

target_link_libraries(solarfox PRIVATE arcadeGlobal)

set_target_properties(solarfox PROPERTIES
    PREFIX "arcade_"
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib
)

# --- GRAPHIC MODULES ---
# --- SDL2 ---
add_library(sdl2 SHARED
    source/module/graphic/SDL2Display.cpp
    source/module/ADisplayModule.cpp
)

target_link_libraries(sdl2 PRIVATE
    arcadeGlobal
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf
)

set_target_properties(sdl2 PROPERTIES
    PREFIX "arcade_"
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib
)

# --- NCURSES ---
find_package(Curses REQUIRED)

add_library(ncurses SHARED
    source/module/graphic/NCURSESDisplay.cpp
    source/module/ADisplayModule.cpp
)

target_include_directories(ncurses PRIVATE ${CURSES_INCLUDE_DIRS})

target_link_libraries(ncurses PRIVATE
    arcadeGlobal
    ${CURSES_LIBRARIES}
)

set_target_properties(ncurses PROPERTIES
    PREFIX "arcade_"
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib
)

# --- TESTS ---
find_package(PkgConfig QUIET)
if(PKG_CONFIG_FOUND)
    pkg_check_modules(CRITERION criterion QUIET)
endif()

if(CRITERION_FOUND)
    file(GLOB TEST_FILES CONFIGURE_DEPENDS "tests/*.cpp")
    add_executable(tests_run ${TEST_FILES})

    # Link with common flags and Criterion
    target_link_libraries(tests_run PRIVATE arcadeGlobal ${CRITERION_LIBRARIES})
    target_include_directories(tests_run PRIVATE ${CRITERION_INCLUDE_DIRS})

    enable_testing()
    add_test(NAME tests COMMAND tests_run)
endif()
