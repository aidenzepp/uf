cmake_minimum_required(VERSION 3.26)
project(project_2)

set(CMAKE_CXX_STANDARD 14)


# Recommended by professor to match test environment.
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )


# Pull in the desired Catch Framework version of catch through cmake.
Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0
)
FetchContent_MakeAvailable(Catch2)

# Add necessary directories.
include_directories(src)
include_directories(test)

# --- Main ---
add_executable(Main
        src/main.cpp
        src/Clap.cpp
        src/Clap.h
        src/Graph.cpp
        src/Graph.h
)

# --- Test ---
add_executable(Test
        test/test.cpp
        src/Clap.cpp
        src/Clap.h
        src/Graph.cpp
        src/Graph.h
)

target_link_libraries(Test PRIVATE Catch2::Catch2WithMain)
