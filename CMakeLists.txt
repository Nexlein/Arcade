cmake_minimum_required(VERSION 3.27)
project(Arcade)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/interface
    ${CMAKE_SOURCE_DIR}/include/core
    ${CMAKE_SOURCE_DIR}/include/module
    ${CMAKE_SOURCE_DIR}/include/module/game
    ${CMAKE_SOURCE_DIR}/include/module/graphic
    ${CMAKE_SOURCE_DIR}/include/module/menu
)

# Core library
file(GLOB CORE_FILES
    "source/core/*.cpp"
    "source/module/*.cpp"
    "source/main.cpp"
)

# Game and Graphic libraries
file(GLOB GAME_FILES "source/module/game/*.cpp" "source/module/menu/*.cpp")
file(GLOB GRAPHIC_FILES "source/module/graphic/*.cpp")

# Core Project
add_executable(arcade ${CORE_FILES})
target_compile_options(arcade PRIVATE
    -Wall
    -Wextra
    -Werror
    -Wunused
    -ldl
)

foreach(file ${GAME_FILES})
    cmake_path(GET file STEM name)

    add_library(${name} SHARED ${file} source/module/AGameModule.cpp)

    set_target_properties(${name} PROPERTIES PREFIX "")
    target_compile_options(${name} PRIVATE -fPIC -Wall -Wextra -Werror)
endforeach()

foreach(file ${GRAPHIC_FILES})
    cmake_path(GET file STEM name)

    add_library(${name} SHARED ${file} source/module/ADisplayModule.cpp)

    set_target_properties(${name} PROPERTIES PREFIX "")
    target_compile_options(${name} PRIVATE -fPIC -Wall -Wextra -Werror)
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
