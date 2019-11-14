#!/bin/bash

if [ $# -ne 1 ]; then
  echo "Usage: $0 [LLVM Path]";
  exit 1;
fi

dir=$1;
if [ ! -d "$dir" ]; then
  echo "Invalid path: ${dir}";
  exit 1;
fi

rm -rf build
mkdir build
cd build 
cmake -DBUILD_SHARED_LIBS=ON $1 ..
#make -j8


