#include "Headers/llvm_context.h"

Context::Context() {
    this->moduleOb = new Module("Decaf Compiler", llvmContext);
    this->builder = new IRBuilder<>(llvmContext);
    this->loops = new std::stack<loopInfo*>();
}

AllocaInst* Context::createLocalVarFunction(Function *function, char* id, char* type) {
    IRBuilder<> builder(&function->getEntryBlock(), function->getEntryBlock().begin());
    
    if (type == "int") {
        return builder.CreateAlloca(Type::getInt32Ty(this->llvmContext), 0, id);
    }
    else if (type == "boolean") {
        return builder.CreateAlloca(Type::getInt1Ty(this->llvmContext), 0, id);
    }

    return nullptr;
}