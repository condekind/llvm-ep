#include "llvm/Pass.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Support/raw_ostream.h"

#define DEBUG_TYPE "EdgeCounter"

using namespace llvm;

// these macros are used to record edge-related information.
STATISTIC(numEdges, "Number of edges");

namespace {
struct EdgeCounter : public llvm::BasicBlockPass
{

  public:
	static char ID;
	EdgeCounter() : BasicBlockPass(ID) {}
	virtual ~EdgeCounter() {}

	virtual bool runOnBasicBlock(BasicBlock &BB)
	{
		Instruction *ins = BB.getTerminator();
		numEdges += ins->getNumSuccessors();
		return true;
	} // runOnBasicBlock

}; // end of pass
} // end of namespace: llvm


char EdgeCounter::ID = 0;
static RegisterPass<EdgeCounter> X("EdgeCounter", "Edge count pass", false, false);
