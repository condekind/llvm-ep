

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

## Don't know why this is needed.
#execute_process (COMMAND llvm-config --cxxflags --ldflags OUTPUT_VARIABLE LLVM_CONFIG_N)
#string (REPLACE "\n" " " LLVM_CONFIG "${LLVM_CONFIG_N}")

## Specifies custom flags for compilation. "-undefined dynamic_lookup" is OSX specific.
#set (CMAKE_CXX_FLAGS "-O3 -g ${LLVM_CONFIG} -undefined dynamic_lookup")

## default
#include_directories (include)
#add_library (RangeAnalysis SHARED
#  path/to/file1.cpp
#  path/to/file2.cpp
#  path/to/file3.cpp
#)
