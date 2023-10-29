cmake_minimum_required(VERSION 3.26)
project(project_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(project_1 main.cpp
        Node.cpp
        Node.h
        Clap.cpp
        Clap.h
)
