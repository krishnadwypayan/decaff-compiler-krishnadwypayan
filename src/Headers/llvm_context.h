#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

using namespace llvm;

class Context {
public:
    LLVMContext &context;

    Module *moduleObject;

    Context();
};