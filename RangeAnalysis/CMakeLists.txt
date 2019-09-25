cmake_minimum_required (VERSION 3.9)

project (RangeAnalysis)

find_package(LLVM REQUIRED CONFIG)

execute_process (COMMAND llvm-config --cxxflags --ldflags OUTPUT_VARIABLE LLVM_CONFIG_N)

include_directories(${LLVM_INCLUDE_DIRS})

string (REPLACE "\n" " " LLVM_CONFIG "${LLVM_CONFIG_N}")

set (CMAKE_CXX_FLAGS "-std=c++14 -fno-rtti -O3 -g ${LLVM_CONFIG} -undefined")

include_directories (include)
add_library (RangeAnalysis SHARED
lib/RangeAnalysis/RangeAnalysis.cpp
lib/RangeAnalysis/vSSA.cpp
lib/RangeAnalysis/ClientRA.cpp
)
