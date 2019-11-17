

cmake_minimum_required (VERSION 3.9)
project(EXTRAPASSES)                  # project name
find_package(LLVM 10 REQUIRED CONFIG)    # needed for out-of-tree pass

list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(AddLLVM)

add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})

add_subdirectory(EdgeCounter)
add_subdirectory(VarCounter)

#
