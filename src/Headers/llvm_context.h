#ifndef DECAF_LLVM_CONTEXT
#define DECAF_LLVM_CONTEXT

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include <llvm/Support/raw_ostream.h>
#include <bits/stdc++.h>

using namespace llvm;
using namespace std;

class loopInfo {
    // BasicBlock that corresponds to the block that should follow the current block
    BasicBlock *afterBB, *checkBB;
    
    // Looping condition
    Value *condition;
    
    // The loop variable used in the looping condition
    string loopVariable;
    
    // PHINode
    PHINode *phiVariable;

public:
    loopInfo(BasicBlock *afterBlock, BasicBlock *checkBlock, Value *cond, std::string var, PHINode *phiVar) {
        afterBB = afterBlock;
        checkBB = checkBlock;
        condition = cond;
        loopVariable = var;
        phiVariable = phiVar;
    }

    // Basic getters for each of the loopInfo members

    BasicBlock *getAfterBlock() { 
        return afterBB; 
    }

    BasicBlock *getCheckBlock() { 
        return checkBB; 
    }

    Value *getCondition() { 
        return condition; 
    }

    PHINode *getPHINode() { 
        return phiVariable; 
    }

    string getLoopVariable() { 
        return loopVariable; 
    }
};

class Context {
public:
    Context();

    // LLVMContext (opaquely) owns and manages the core "global" data of LLVM's core infrastructure, 
    // including the type and constant uniquing tables. LLVMContext itself provides no locking 
    // guarantees, so you should be careful to have one context per thread.
    LLVMContext llvmContext;

    // A Module instance is used to store all the information related to an LLVM module. Modules 
    // are the top level container of all other LLVM Intermediate Representation (IR) objects. 
    // Each module directly contains a list of globals variables, a list of functions, a list 
    // of libraries (or other modules) this module depends on, a symbol table, and various data 
    // about the target's characteristics.
    Module *moduleOb;

    // IRBuilder provides a uniform API for creating instructions and inserting them into a basic block: 
    // either at the end of a BasicBlock, or at a specific iterator location in a block.
    IRBuilder<> *builder;

    // The NamedValues map keeps track of which values are defined in the current scope and what their 
    // LLVM representation is. (In other words, it is a symbol table for the code).
    map<char*, AllocaInst*> NamedValues;

    // Method that allocates memory for variables of a function on the stack of the function by
    // creating an AllocaInst
    AllocaInst* createLocalVarFunction(Function *function, char* id, char* type);

    // Stack of loopInfo objects is used to store the basic blocks information involved in loops.
    // The top of the stack stores the current loop block.
    std::stack<loopInfo*> *loops;
};

#endif // DECAF_LLVM_CONTEXT