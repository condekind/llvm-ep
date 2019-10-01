#include "llvm/Pass.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Support/raw_ostream.h"

#define DEBUG_TYPE "EdgeCounter"

using namespace llvm;

// these macros are used to record variable-related information.
STATISTIC(numEdges, "Number of edges.");

namespace {
struct EdgeCounter : public llvm::BasicBlock
{

  public:

	static char ID;
	EdgeCounter() : BasicBlock(ID) {}
	virtual ~EdgeCounter() {}

	// iterating through functions
	virtual bool runOnBasicBlock(BasicBlock &BB)
	{
		Instruction *ins = BB.getTerminator();
		numEdges += ins->getNumSuccessors();
	} // runOnBasicBlock

}; // end of pass
} // end of namespace: llvm


char EdgeCounter::ID = 0;
static RegisterPass<EdgeCounter> X("EdgeCounter", "Edge count pass.", false, false);