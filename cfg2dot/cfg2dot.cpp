#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/FormattedStream.h"
#include <fstream>
#include <sstream>
#include <string>
#include <map>

// Assignment 1 - DCC888

// Bruno Conde Kind     - M: 2013007170
// Jerônimo Nunes Rocha - M: 2013069108

using namespace llvm;

namespace {

	struct CFG2DOT : public FunctionPass {

		static char ID;

		CFG2DOT () : FunctionPass(ID) {}

		bool runOnFunction(Function &F) override {

			long blockCnt = 1;
			std::string dotstr;

			long nextUniqueName = 0;
			std::map<std::string, long> addr2name;

			dotstr += "digraph \"CFG for '";
			dotstr += F.getName().data();
			dotstr += "' function\" {\n";

			// naming all the basic blocks
			for(Function::iterator fit = F.begin(); fit != F.end(); fit++)
			{
				if ((*fit).hasName() == false)
				{
					fit->setName(std::string("BB") + std::to_string(blockCnt++));
				}
			}

			// iterating through basic blocks
			for(Function::iterator fit = F.begin(); fit != F.end(); fit++)
			{
				BasicBlock &BB = *fit;

				dotstr += "         ";
				dotstr += fit->getName();
				dotstr += "[shape=record,\n            label=\"{";
				dotstr += fit->getName();
				dotstr += ":\\l\\l\n";

				// iterating through instructions
				Instruction *lastInst;
				for(BasicBlock::iterator bbit = BB.begin(); bbit != BB.end(); bbit++)
				{
					Instruction *ins = &*bbit;

					std::stringstream ss;

					const char* aux = reinterpret_cast<const char*>(&ins);
					std::string insName = aux;

					if (addr2name[insName] == 0)
						addr2name[insName] = nextUniqueName++;

					ss  << "                    %"
						<< addr2name[insName]
						<< " = " 
						<< (*ins).getOpcodeName()
						<< ": ";

					// iterating through operands of the current instruction
					for(unsigned int i = 0; i < (*ins).getNumOperands(); i++ )
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
						
					}
					ss << "\\l\n";
					dotstr += ss.str();
					lastInst = ins;
				}
				dotstr.pop_back();
				dotstr += "}\"];\n";

				// generating edges
				int numSucc = lastInst->getNumSuccessors();
				for(int i = 0; i < numSucc; i++)
				{
					dotstr += "         ";
					dotstr += fit->getName();
					dotstr += " -> ";
					dotstr += lastInst->getSuccessor(i)->getName();
					dotstr += ";\n";
				}
			}

			dotstr += "}\n";

			// output to .dot file
			std::ofstream ofs;
			std::string filename;
			filename += F.getName().data();
			filename += ".dot";
			ofs.open (filename, std::fstream::out | std::fstream::trunc);
			ofs << dotstr;
			ofs.close();

			return false;
		}

	};

}


char CFG2DOT::ID = 0;

static RegisterPass<CFG2DOT> X("cfg2dot", "CFG to dot graph pass", false, false);