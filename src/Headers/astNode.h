#ifndef DECAF_COMPILER_ASTNODE_H
#define DECAF_COMPILER_ASTNODE_H

#include "llvm_context.h"
#include <bits/stdc++.h>
#include <llvm/IR/Value.h>

using namespace llvm;
using namespace std;

class ASTnode {
public:
    virtual Value* codeGen(Context *context) {}

};

#endif // !DECAF_COMPILER_ASTNODE_H