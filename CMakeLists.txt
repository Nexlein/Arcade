cmake_minimum_required(VERSION 3.17)
project(Arcade)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/Include)

file(GLOB PROJECT_FILES
)

add_executable(arcade Source/main.cpp ${PROJECT_FILES})
target_compile_options(arcade PRIVATE
    -Wall
    -Wextra
    -Werror
    -Wunused
)

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
    add_test(NAME components_tests COMMAND tests_run)
endif()
