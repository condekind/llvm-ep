#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/User.h"
#include "llvm/PassAnalysisSupport.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm-c/Core.h"
#include "include/RangeAnalysis.h"

using namespace llvm;

namespace {

  class ClientRA : public llvm::FunctionPass {

  public:

    static char ID;

    ClientRA() : FunctionPass(ID) {}

    virtual ~ClientRA() {}

    // -1 always false, 0 can't tell, 1 always true
    int handleCmp(CmpInst *cmpInst, InterProceduralRA<Cousot> *ra)
    {

      Range r[2];
      r[0] = ra->getRange(cmpInst->getOperand(0));
      r[1] = ra->getRange(cmpInst->getOperand(1));

      for (unsigned int i = 0; i < (*cmpInst).getNumOperands(); i++ )
      {
        if ( isa<ConstantInt>(cmpInst->getOperand(i)) )
        {
          ConstantInt *auxCI = dyn_cast<llvm::ConstantInt>(cmpInst->getOperand(i));
          const APInt &auxAPInt = auxCI->getValue();
          r[i].setRegular();
          r[i].setLower( auxAPInt );
          r[i].setUpper( auxAPInt );
        }
      }

      // A bit width assertion error might indicate a vulnerability.
      // Tested with the sample program from tainted flow analysis lecture (3)
      switch (cmpInst->getPredicate())
      {
      case CmpInst::ICMP_EQ: // equal
        if (r[0].getLower() == r[1].getLower() == r[0].getUpper() == r[1].getUpper())
          return 1;
        if (cmpInst->isSigned())
        {
          if (r[0].getUpper().slt(r[1].getLower())) return -1;
          if (r[1].getUpper().slt(r[0].getLower())) return -1;
        }
        else
        {
          if (r[0].getUpper().ult(r[1].getLower())) return -1;
          if (r[1].getUpper().ult(r[0].getLower())) return -1;
        }
        return 0;

      case CmpInst::ICMP_NE: // not equal
        if (r[0].getLower() == r[1].getLower() == r[0].getUpper() == r[1].getUpper())
          return -1;
        if (cmpInst->isSigned())
        {
          if (r[0].getUpper().slt(r[1].getLower())) return 1;
          if (r[1].getUpper().slt(r[0].getLower())) return 1;
        }
        else
        {
          if (r[0].getUpper().ult(r[1].getLower())) return 1;
          if (r[1].getUpper().ult(r[0].getLower())) return 1;
        }
        return 0;

      case CmpInst::ICMP_UGT: // unsigned greater than
        if (r[0].getLower().ugt(r[1].getUpper())) return 1;
        if (r[0].getUpper().ule(r[1].getLower())) return -1;
        return 0;

      case CmpInst::ICMP_UGE: // unsigned greater or equal
        if (r[0].getLower().uge(r[1].getUpper())) return 1;
        if (r[0].getUpper().ult(r[1].getLower())) return -1;
        return 0;

      case CmpInst::ICMP_ULT: // unsigned less than
        if (r[0].getUpper().ult(r[1].getLower())) return 1;
        if (r[0].getLower().uge(r[1].getUpper())) return -1;
        return 0;

      case CmpInst::ICMP_ULE: // unsigned less or equal
        if (r[0].getUpper().ule(r[1].getLower())) return 1;
        if (r[0].getLower().ugt(r[1].getUpper())) return -1;
        return 0;

      case CmpInst::ICMP_SGT: // signed greater than
        if (r[0].getLower().sgt(r[1].getUpper())) return 1;
        if (r[0].getUpper().sle(r[1].getLower())) return -1;
        return 0;

      case CmpInst::ICMP_SGE: // signed greater or equal
        if (r[0].getLower().sge(r[1].getUpper())) return 1;
        if (r[0].getUpper().slt(r[1].getLower())) return -1;
        return 0;

      case CmpInst::ICMP_SLT: // signed less than
        if (r[0].getUpper().slt(r[1].getLower())) return 1;
        if (r[0].getLower().sge(r[1].getUpper())) return -1;
        return 0;

      case CmpInst::ICMP_SLE: // signed less or equal
        if (r[0].getUpper().sle(r[1].getLower())) return 1;
        if (r[0].getLower().sgt(r[1].getUpper())) return -1;
        return 0;

      default:
        return 0;
      }

    }


    virtual bool runOnFunction(Function &F)
    {

      InterProceduralRA<Cousot>::ID=0;
      InterProceduralRA<Cousot> &ra = getAnalysis<InterProceduralRA<Cousot>>();

      errs() << "LLVMICmp: " << LLVMICmp << ", LLVMFCmp: " << LLVMFCmp;
      errs() << ", LLVMIndirectBr: " << LLVMIndirectBr;
      errs() << ", LLVMBr: " << LLVMBr << "\n\n";
      errs() << "\nCousot Intra Procedural analysis (Values -> Ranges) of ";
      errs() << F.getName() << ":\n\n";

      for (Function::iterator fit = F.begin(); fit != F.end(); fit++)
      {
        BasicBlock &BB = *fit;

        std::map<std::string, int> cmpMap;

        for (BasicBlock::iterator bbit = BB.begin(); bbit != BB.end(); bbit++)
        {
          Instruction *ins = &*bbit;
          const Value *v = &(*bbit);
          Range r = ra.getRange(v);

          r.print(errs());
          ins->dump();

          if ( CmpInst *cmpInst = dyn_cast<CmpInst>(ins) ) // icmp
          {

            std::stringstream auxstream;
            auxstream << (void *)ins;
            std::string insName = auxstream.str();
            cmpMap[insName] = handleCmp(cmpInst, &ra);
            continue;

          }

          if ( BranchInst *brInst = dyn_cast<BranchInst>(ins) ) // br
          {

            if (brInst->isUnconditional()) // not interesting
              continue;

            BranchInst *newBrInst;
            std::stringstream auxstream;
            auxstream << (void *)ins->getOperand(0);
            std::string insName = auxstream.str();

            // Checking the range of the branch condition
            Range rb = ra.getRange((const Value *)ins->getOperand(0));
            if ( rb.getLower().isStrictlyPositive() )
            {
              cmpMap[insName] = 1;
              r.setRegular();
              r.setLower(rb.getLower());
              r.setUpper(rb.getUpper());
            }
            if ( rb.getUpper().isNegative() )
            {
              cmpMap[insName] = 1;
              r.setRegular();
              r.setLower(rb.getLower());
              r.setUpper(rb.getUpper());
            }
            if ( rb.getLower() == rb.getUpper() && rb.getLower().isNullValue() )
            {
              cmpMap[insName] = -1;
              r.setRegular();
              r.setLower(rb.getLower());
              r.setUpper(rb.getUpper());
            }

            errs() << "this condition is " << known[cmpMap[insName]] << "\n\n";

            switch (cmpMap[insName])
            {

            case 1: // always true, take 1st branch
              newBrInst = BranchInst::Create(brInst->getSuccessor(0));
              ReplaceInstWithInst(ins->getParent()->getInstList(), bbit, newBrInst);
              ins = newBrInst;
              break;

            case -1: // always false, take 2nd branch
              newBrInst = BranchInst::Create(brInst->getSuccessor(1));
              ReplaceInstWithInst(ins->getParent()->getInstList(), bbit, newBrInst);
              ins = newBrInst;
              break;

            case 0: // can't tell, do nothing
              break;

            default:
              break;

            }

            continue;

          }

        }

      }

      return false;

    }


    virtual void getAnalysisUsage(AnalysisUsage &AU) const
    {

      AU.setPreservesAll();
      AU.addRequired<InterProceduralRA<Cousot> >();

    }


  private:

    std::map<int, std::string> known = {{-1, "always false"},
                                        {0, "inconclusive"},
                                        {1, "always true"}};

  };
}

char ClientRA::ID = 0;
static RegisterPass<ClientRA> X("dead-code-elim",
                                "A client that uses RangeAnalysis");
