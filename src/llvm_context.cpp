#include "Headers/llvm_context.h"

Context::Context() {
    this->moduleOb = new Module("Decaf Compiler", llvmContext);
    this->builder = new IRBuilder<>(llvmContext);
}