

cmake_minimum_required (VERSION 3.9)
project(EXTRAPASSES)                  # project name
find_package(LLVM REQUIRED CONFIG)    # needed for out-of-tree pass

list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(AddLLVM)

add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})

add_subdirectory(EdgeCounter)
add_subdirectory(VarCounter)


## default
#project (NAME)
#find_package(LLVM REQUIRED CONFIG)
#include_directories(${LLVM_INCLUDE_DIRS})


## default
#include_directories (include)
#add_library (RangeAnalysis SHARED
#  path/to/file1.cpp
#  path/to/file2.cpp
#  path/to/file3.cpp
#)
