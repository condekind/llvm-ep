



Assignment 2 - DCC888

Bruno Conde Kind     - M: 2013007170
Jerônimo Nunes Rocha - M: 2013069108




The pass should be compiled outside the LLVM tree. There is a build.sh script
that should be run to compile the pass, as follows:
$ ./build.sh .../path-to-llvm/build

Then, there's an execute.sh script to run the pass. Run it as:
$ ./execute.sh .../path-to-llvm .../path-to-test-program.cpp

The execute script is pretty straightforward. In the end it will generate pdf's
with side to side comparisons of the dot graphs for each function in the
program. If a better look at the .ll or .dot files is desired, the script
should be changed as not to remove these files.

The pass does remove dead code, however there are a few important notes:

  1. The most interesting thing I noted was an error when running the
pass on the sample program of the tainted flow analysis lecture, found on:

  ./tests/3/03.cpp

   The problem was a runtime assertion error when the program compares a
constant i:32 with an i:8 (originally a char in the source file). I decided not
to fix this 'feature'. I could've written an exception handling block around
this, however I found it pretty cool to forbid the programmer to carry on with
such a potential flaw.

  2. Sometimes the program size *increases*! This happens because of sigma/phi
nodes. It can be observed when the pass is run on:

  ./tests/2/02.cpp

  3. The statistics print was not tested due to a time constraint, so it is
probably wrong, since when swapping conditional branches for inconditional ones
we didn't update any counters.

  4. The graphs generated are only valid because we run the -simplifycfg pass.
Without it, the graphs contain unreachable nodes, which we didn't manually
remove. That is another reason for why the statistics are probably wrong: we're
not counting how many instructions are removed, we simply remove edges and rely
on the auxiliary pass to trim the blocks, should they be unreachable. If we
were to do this, we'd insert a store with an undef value in each block
to be removed, counting instructions contained in these blocks.

  5. The file is still called ClientRA.cpp, we didn't update the library names.
We hope this won't be a problem.

Final considerations:

  NONE of this work would be possible without the help of Angelica. She helped
in ways no Stack Overflow page could. In fact, 99% of the code behind the
build.sh and execute.sh scripts are hers. It is important to us to make this
clear, as there was no intention of plagiarism. We simply wanted to be able
to carry on with the actual task, and a lot of time was spent trying to figure
how to do this on our on. In the end we decided to use her approach, for which
we are very very grateful.
