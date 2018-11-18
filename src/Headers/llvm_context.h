#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include <llvm/Support/raw_ostream.h>
#include <bits/stdc++.h>

using namespace llvm;
using namespace std;

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
};