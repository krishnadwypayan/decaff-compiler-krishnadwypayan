#include "Headers/methodDeclarations.h"


// --------- Class definitions for class MethodDeclarations ---------- //
void MethodDeclarations::addMethodDecl(class MethodDeclaration *methodDecl) {
    this->methodsVector.push_back(methodDecl);
}

Value* MethodDeclarations::codeGen(Context *context) {
    Value *value = ConstantInt::get(context->llvmContext, APInt(32, 0));
    for (auto &method : methodsVector) {
        value = method->codeGen(context);
        if (value == nullptr) {
            cerr << "[error] code gen for method returned null \n";
            return nullptr;
        }
    }

    return value;
}

// --------- Class definitions for class MethodDeclaration ----------- //
MethodDeclaration::MethodDeclaration(char* type, char* methodName, class MethodArgs *methodArgs, class Block *block) {
    this->type = type;
    this->methodName = methodName;
    this->methodArgs = methodArgs;
    this->block = block;
}

Value* MethodDeclaration::codeGen(Context *context) {
    vector<char*> argNames;
    vector<char*> argTypes;
    vector<class MethodArg*> args = methodArgs->getMethodArgs();
    vector<Type*> arguments;

    // iterate over args and get type in llvm
    for (auto &arg : args) {
        char* argType = arg->getArgType();
        char* argName = arg->getArgName();

        if (argType == "int") {
            arguments.push_back(Type::getInt32Ty(context->llvmContext));
        }
        else if (argType == "boolean") {
            arguments.push_back(Type::getInt1Ty(context->llvmContext));
        }
        else {
            cerr << "[error] wrong argument type given \n";
            return nullptr;
        }

        argTypes.emplace_back(argType);
        argNames.emplace_back(argName);
    }

    // get the return type for the function
    Type *returnType;
    if (type == "int") {
        returnType = Type::getInt32Ty(context->llvmContext);
    }
    else if (type == "boolean") {
        returnType = Type::getInt1Ty(context->llvmContext);
    }
    else if (type == "void") {
        returnType = Type::getVoidTy(context->llvmContext);
    }
    else {
        cerr << "[error] invalid return type \n";
        return nullptr;
    }

    // create the function
    FunctionType *funcType = FunctionType::get(returnType, arguments, false);
    Function *function = Function::Create(funcType, Function::ExternalLinkage, methodName, context->moduleOb);

    // iterate throught the arguments
    auto argsSize = args.size();
    unsigned idx = 0;
    for (Function::arg_iterator argIt = function->arg_begin(); idx != argsSize; argIt++, idx++) {
        argIt->setName(argNames[idx]);
    }

    // create a new basic block for this function
    BasicBlock *functionBB = BasicBlock::Create(context->llvmContext, "funcBlock", function);
    context->builder->SetInsertPoint(functionBB);

    // allocate memory for args
    idx = 0;
    for (auto &arg : function->args()) {
        AllocaInst *alloca = context->createLocalVarFunction(function, argNames[idx], argTypes[idx]);
        context->builder->CreateStore(&arg, alloca);
        context->NamedValues[argNames[idx]] = alloca;
        idx++;
    }

    // generate code for the body of the function
    Value *value = block->codeGen(context);
    if (value != nullptr) {
        if (type != "void") {
            context->builder->CreateRet(value);
        }
        else {
            context->builder->CreateRetVoid();
        }

        verifyFunction(*function);
        return function;
    }

    function->eraseFromParent();
    return nullptr;
}

// ------------ Class definitions for class MethodArgs --------------- //
void MethodArgs::addMethodArg(class MethodArg *methodArg) {
    this->methodArgsVector.push_back(methodArg);
}

// ------------ Class definitions for class MethodArg ---------------- //
MethodArg::MethodArg(char* type, char* name) {
    this->type = type;
    this->name = name;
}
