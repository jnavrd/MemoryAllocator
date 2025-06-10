cmake_minimum_required(VERSION 3.26)
project(MemoryAllocator)

set(CMAKE_CXX_STANDARD 17)

add_executable(MemoryAllocator main.cpp
        memory/PoolAllocator.h
        memory/PoolAllocator.cpp
        memory/VariableSizeAllocator.h
        memory/VariableSizeAllocator.cpp)
