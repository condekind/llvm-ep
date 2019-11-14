#include "llvm/Pass.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Support/raw_ostream.h"
#include <cstdint>
#include <map>

#define DEBUG_TYPE "VarCounter"

using namespace llvm;

// these macros are used to record variable-related information.
STATISTIC(usedVars, "Number of named variable uses");
STATISTIC(namedVars, "Number of named variables");

namespace {
struct VarCounter : public llvm::FunctionPass
{

  public:

	static char ID;
	VarCounter() : FunctionPass(ID) {}
	virtual ~VarCounter() {}

	std::map<std::uintptr_t, bool> nameBook;
	std::map<std::uintptr_t, bool> VarCount;

	// iterating through functions
	virtual bool runOnFunction(Function &F)
	{
		// function iteration
		for(Function::iterator fit = F.begin(); fit != F.end(); fit++)
		{
			// basic block iteration
			BasicBlock &BB = *fit;
			for(BasicBlock::iterator bbit = BB.begin(); bbit != BB.end(); bbit++)
			{
				// operand iteration
				Instruction *ins = &*bbit;
				for( unsigned int i = 0; i < (*ins).getNumOperands(); i++ )
				{
					Value *v = ins->getOperand(i);

					if ( !(v->hasName()) )
						continue;

					std::uintptr_t var = reinterpret_cast<std::uintptr_t>(v);

					// increment count for new named variables
					if ( !(nameBook[var]) )
					{
						nameBook[var] = true;
						namedVars++;
					}

					// get count of all uses of this new named variable
					if ( !VarCount[var] )
					{
						VarCount[var] = true;
						usedVars += v->getNumUses();
					}

				} // operand iteration
			} // basic block iteration
		} // funtion iteration

		return true;
	} // runOnFunction



}; // end of pass
} // end of namespace: llvm


char VarCounter::ID = 0;
static RegisterPass<VarCounter> X("VarCounter",
    "Named variables and variable use count pass", false, false);
