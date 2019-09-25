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
suffix="so"
if [[ $(uname -s) == "Linux" ]]; then
  suffix="so"
fi

script_path="$( cd "$(dirname "$0")" ; pwd -P )"
program=${2%.*}
extension=${2#*.}
program_ll=${program}.ll
program_file=$2
program_file_name=$(basename -- "$2")
extension=${program_file_name#*.}
program_file_name=${program_file_name%.*}
pass_path="$(dirname "$script_path")"
range_analysis=${script_path}/build/libRangeAnalysis.$suffix

echo $range_analysis

directory_name="$(dirname "$program")"
#clean all files from the current program files
function clean() {
  echo "Removing old files."
  rm -f *.bc
  rm -f *.ll
  rm -f *.o
  rm -f *.exe
  rm -f *.out
  rm -f *.before.pdf
  rm -f *.after.pdf
  rm -f *.comparison.pdf
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
  $dir/build/bin/opt -instnamer -mem2reg -break-crit-edges $program_ll -S -o $program_ll

  echo "======================== Generating the cfg pre pass  ========================="
  $dir/build/bin/opt -dot-cfg $program_ll -disable-output
  for file in .[^.]*.dot; do mv $file $file.before.dot; done;
  #dot -Tpdf .[^.]*.dot -o $program_ll.before.pdf

  echo "=== Loading Dead Code Elimination Analysis pass with some auxiliary passes ===="
  $dir/build/bin/opt -load $range_analysis -vssa -dead-code-elim -stats -simplifycfg -S -o=$program_ll < $program_ll

  echo "======================= Generating the cfg.dot files =========================="
  $dir/build/bin/opt -dot-cfg $program_ll -disable-output
  for file in .[^.]*[^after].dot; do mv $file $file.after.dot; done;
  #dot -Tpdf .[^.]*.dot -o $program_ll.after.pdf

  for file in .*before.dot; do nhfile=${file#.}; gvpack ${file} ${file/before/after} -u | dot -Tpdf -o "${nhfile/\.before\.dot/}.comparison.pdf"; done;
}
   

rm -f .[^.]*.dot
cd $directory_name
clean ;
cd $script_path
compile ;
load ;
rm -f .[^.]*.dot
