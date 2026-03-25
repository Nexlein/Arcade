cmake_minimum_required(VERSION 3.27)
project(Arcade)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Libraries -> lib/
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

include(FetchContent)

# Force SDL to be built as a shared library
set(SDL_SHARED ON CACHE BOOL "Build SDL shared library" FORCE)
set(SDL_STATIC OFF CACHE BOOL "Build SDL static library" FORCE)

message(STATUS "Fetching SDL2...")
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        release-2.30.0
)
FetchContent_MakeAvailable(SDL2)

message(STATUS "Fetching SDL2_image...")
FetchContent_Declare(
    SDL2_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG        release-2.8.2
)
FetchContent_MakeAvailable(SDL2_image)

message(STATUS "Fetching SDL2_ttf...")
FetchContent_Declare(
    SDL2_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG        release-2.22.0
)
FetchContent_MakeAvailable(SDL2_ttf)

# GLOBAL INCLUDES
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/interface
    ${CMAKE_SOURCE_DIR}/include/core
    ${CMAKE_SOURCE_DIR}/include/module
    ${CMAKE_SOURCE_DIR}/include/module/game
    ${CMAKE_SOURCE_DIR}/include/module/graphic
    ${CMAKE_SOURCE_DIR}/include/module/menu
)

# CORE PROJECT
file(GLOB CORE_FILES
    "source/core/*.cpp"
    "source/module/*.cpp"
    "source/main.cpp"
)

add_executable(arcade ${CORE_FILES})
target_compile_options(arcade PRIVATE -Wall -Wextra -Werror -Wunused)
target_link_libraries(arcade PRIVATE ${CMAKE_DL_LIBS}) 

# GAME MODULES
file(GLOB GAME_FILES "source/module/game/*.cpp" "source/module/menu/*.cpp")

foreach(file ${GAME_FILES})
    cmake_path(GET file STEM name)
    add_library(${name} SHARED ${file} source/module/AGameModule.cpp)
    set_target_properties(${name} PROPERTIES PREFIX "")
    target_compile_options(${name} PRIVATE -Wall -Wextra -Werror)
endforeach()

# GRAPHIC MODULES

# SDL2
add_library(arcade_sdl2 SHARED source/module/graphic/SDL2Display.cpp source/module/ADisplayModule.cpp)
set_target_properties(arcade_sdl2 PROPERTIES PREFIX "")
target_compile_options(arcade_sdl2 PRIVATE -Wall -Wextra -Werror)
target_link_libraries(arcade_sdl2 PRIVATE SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)

# TESTS
find_package(PkgConfig QUIET)
if (PKG_CONFIG_FOUND)
    pkg_check_modules(CRITERION criterion)
endif()

if (CRITERION_FOUND)
    file(GLOB TEST_FILES tests/*.cpp)
    add_executable(tests_run ${TEST_FILES}) 
    target_compile_options(tests_run PRIVATE -Wall -Wextra -Werror -Wunused)
    target_include_directories(tests_run PRIVATE ${CRITERION_INCLUDE_DIRS})
    target_link_libraries(tests_run ${CRITERION_LIBRARIES})

    enable_testing()
    add_test(NAME tests COMMAND tests_run)
endif()
