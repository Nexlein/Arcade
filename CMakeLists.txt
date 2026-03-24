cmake_minimum_required(VERSION 3.27)
project(Arcade)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Libraries -> lib/
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

# DEPENDANCES
find_package(PkgConfig REQUIRED)

# IMPORTED_TARGETS -> PkgConfig::SDL2, PkgConfig::SDL2_IMAGE, PkgConfig::SDL2_TTF
pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED IMPORTED_TARGET SDL2_image)
pkg_check_modules(SDL2_TTF REQUIRED IMPORTED_TARGET SDL2_ttf)

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
target_link_libraries(arcade_sdl2 PRIVATE PkgConfig::SDL2 PkgConfig::SDL2_IMAGE PkgConfig::SDL2_TTF)

# TESTS
pkg_check_modules(CRITERION criterion)

if (CRITERION_FOUND)
    file(GLOB TEST_FILES tests/*.cpp)
    add_executable(tests_run ${TEST_FILES}) 
    target_compile_options(tests_run PRIVATE -Wall -Wextra -Werror -Wunused)
    target_include_directories(tests_run PRIVATE ${CRITERION_INCLUDE_DIRS})
    target_link_libraries(tests_run ${CRITERION_LIBRARIES})

    enable_testing()
    add_test(NAME tests COMMAND tests_run)
endif()
