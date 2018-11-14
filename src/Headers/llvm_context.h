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

    LLVMContext llvmContext;

    Module *moduleOb;

    IRBuilder<> *builder;
};