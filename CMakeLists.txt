cmake_minimum_required(VERSION 3.27)
project(Arcade)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/interface
    ${CMAKE_SOURCE_DIR}/include/game
    ${CMAKE_SOURCE_DIR}/include/graphic
    ${CMAKE_SOURCE_DIR}/include/core
    ${CMAKE_SOURCE_DIR}/include/menu
)

# TODO:
# source/module/AGameModule.cpp
# source/module/game/SnakeGame.cpp
# source/module/ADisplayModule.cpp

# Core library
file(GLOB CORE_FILES
    "source/core/*.cpp"
    "source/game/AGameModule.cpp" # TODO: source/module/*.cpp
    "source/main.cpp"
)
# Game and Graphic libraries
file(GLOB GAME_FILES "source/game/*.cpp" "source/menu/*.cpp")
file(GLOB GRAPHIC_FILES "source/graphic/*.cpp")

# Core Project
add_executable(arcade ${CORE_FILES})
target_compile_options(arcade PRIVATE
    -Wall
    -Wextra
    -Werror
    -Wunused
    -ldl
)

# TODO: Change logic to follow the new structure of the project
foreach(file ${GAME_FILES})
    get_filename_component(name ${file} NAME_WE)

    if(NOT name STREQUAL "AGameModule")
        add_library(${name} SHARED ${file} source/game/AGameModule.cpp)

        set_target_properties(${name} PROPERTIES PREFIX "")
        target_compile_options(${name} PRIVATE -fPIC -Wall -Wextra -Werror)
    endif()
endforeach()

foreach(file ${GRAPHIC_FILES})
    get_filename_component(name ${file} NAME_WE)

    if (NOT name STREQUAL "ADisplayModule")
        add_library(${name} SHARED ${file})

        set_target_properties(${name} PROPERTIES PREFIX "")
        target_compile_options(${name} PRIVATE -fPIC -Wall -Wextra -Werror)
    endif()
endforeach()

# Tests
find_package(PkgConfig)

if (PKG_CONFIG_FOUND)
    pkg_check_modules(CRITERION criterion)
endif()

if (CRITERION_FOUND)
    file(GLOB TEST_FILES tests/*.cpp)
    add_executable(tests_run ${TEST_FILES} ${PROJECT_FILES})
    target_compile_options(tests_run PRIVATE
        -Wall
        -Wextra
        -Werror
        -Wunused
    )
    target_include_directories(tests_run PRIVATE ${CRITERION_INCLUDE_DIRS})
    target_link_libraries(tests_run ${CRITERION_LIBRARIES})
    enable_testing()
    add_test(NAME tests COMMAND tests_run)
endif()
