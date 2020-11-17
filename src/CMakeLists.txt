cmake_minimum_required(VERSION 3.17)
project(spl___hw1)

set(CMAKE_CXX_STANDARD 11)

include_directories(./include)

add_executable(ass1
                include/Graph.h
                include/Tree.h
                include/Agent.h
                include/Session.h
                src/main.cpp
                src/Graph.cpp
                src/Session.cpp
                src/Agent.cpp
                src/Tree.cpp)