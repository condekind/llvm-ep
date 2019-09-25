#include "llvm/Pass.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

// these macros are used to record variable-related information.
STATISTIC(usedVars, "Number of variable uses.");
STATISTIC(namedVars, "Number of named variables.");

namespace {
class VarCounter : public llvm::FunctionPass
{

  public:

	static char ID;
	VarCounter() : FunctionPass(ID) {}
	virtual ~VarCounter() {}

	// iterating through functions
	virtual bool runOnFunction(Function &F)
	{
		errs() << "Reading function: " << F.getName() << "\n";
		// iterating through instructions
		for ( Instruction *ins: instructions(f) )
		{
			// iterating through operands of the current instruction
			for( unsigned int i = 0; i < (*ins).getNumOperands(); i++ )
			{
				Value *v = ins->getOperand(i);

				if (v->hasName())
				{
					ss << v->getName().data();
					if (i != (*ins).getNumOperands() - 1)
					{
						ss << ", ";
					}
				}
				else
				{
					aux = reinterpret_cast<const char*>(&v);
					insName = aux;

					if (addr2name[insName] == 0)
						addr2name[insName] = nextUniqueName++;

					ss << "%" << addr2name[insName];
					if (i != (*ins).getNumOperands() - 1)
					{
						ss << ", ";
					}
				}
				
			} // operand iteration

		} // instruction iteration

	} // runOnFunction



};
}