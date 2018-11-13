// #include "Headers/llvm_context.h"

// Context::Context() {
//     Context::context = getGlobalContext();
//     Context::moduleObject = new Module("Decaf Compiler", Context::context);
// }

// int main() {
//     Context context = new Context();
//     context->moduleObject->dump();
//     return 0;
// }

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

using namespace llvm;

static LLVMContext llvmContext;
static Module *ModuleOb = new Module("my compiler", llvmContext);

int main(int argc, char *argv[]) {
    ModuleOb->dump();
    return 0;
}