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
STATISTIC(usedVars, "Number of variable uses.");
STATISTIC(usedVars2, "Number of variable uses (using GetNumUses).");
STATISTIC(namedVars, "Number of named variables.");

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
		errs() << "Reading function: " << F.getName() << "\n";
		for(Function::iterator fit = F.begin(); fit != F.end(); fit++)
		{
			BasicBlock &BB = *fit;
			for(BasicBlock::iterator bbit = BB.begin(); bbit != BB.end(); bbit++)
			{
				Instruction *ins = &*bbit;
				// iterating through operands of the current instruction
				for( unsigned int i = 0; i < (*ins).getNumOperands(); i++ )
				{
					Value *v = ins->getOperand(i);

					std::uintptr_t var = reinterpret_cast<std::uintptr_t>(v);
					usedVars++;

					if ( !VarCount[var] )
					{
						VarCount[var] = true;
						usedVars2 += v->getNumUses();
					}

					// only count named variables that didn't appear yet.
					if ( v->hasName() && !(nameBook[var]) )
					{
						nameBook[var] = true;
						namedVars++;
					}
				} // operand iteration
			} // basic block iteration
		} // funtion iteration

	} // runOnFunction



}; // end of pass
} // end of namespace: llvm


char VarCounter::ID = 0;
static RegisterPass<VarCounter> X("VarCounter", "Named variables and variable use count pass.", false, false);
