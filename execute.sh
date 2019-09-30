#!/bin/bash

if [ $# -ne 2 ]; then
  echo "Usage: $0 [LLVM Path] [Program Path]";
  exit 1;
fi

dir=$1;
if [ ! -d "$dir" ]; then
  echo "Invalid path: ${dir}";
  exit 1;
fi

#set the lib sufix
suffix="dylib"
if [[ $(uname -s) == "Linux" ]]; then
  suffix="so"
fi

script_path="$( cd "$(dirname "$0")" ; pwd -P )"
echo $script_path
program=${2%.*}
extension=${2#*.}
program_ll=${program}.ll
program_file=$2
program_file_name=$(basename -- "$2")
extension=${program_file_name#*.}
program_file_name=${program_file_name%.*}
pass_path="$(dirname "$script_path")"
varCounterPass=${script_path}/build/VarCounter/VarCounter.$suffix

if [ $# -eq 3 ]; then
	OUTFILE=${3}
else
	OUTFILE="output.stats"
fi

echo $varCounterPass

directory_name="$(dirname "$program")"
#clean all files from the current program files
function clean() {
  echo "Removing old files."
  rm -f *.bc
  rm -f *.ll
  rm -f *.o
  rm -f *.exe
  rm -f *.out
}

function compile(){
  echo "Compiling"

  if [ $extension == "cpp" ]
   then
   $dir/build/bin/clang++ -Xclang -disable-O0-optnone -S -emit-llvm -o $program_ll $program_file
  else
   $dir/build/bin/clang -Xclang -disable-O0-optnone -S -emit-llvm -o $program_ll $program_file
   fi
}

function load(){
  echo "========================= Loading some optimizations =========================="
  $dir/build/bin/opt -mem2reg -instnamer -break-crit-edges $program_ll -S -o $program_ll

  echo "=== Loading varCounter pass with some auxiliary passes ===="
  $dir/build/bin/opt -load $varCounterPass -VarCounter -stats -S -disable-output < $program_ll 2>> $OUTFILE
}
   

cd $directory_name
clean ;
cd $script_path
compile ;
load ;
