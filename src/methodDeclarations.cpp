#include "Headers/methodDeclarations.h"


// --------- Class definitions for class MethodDeclarations ---------- //
void MethodDeclarations::addMethodDecl(class MethodDeclaration *methodDecl) {
    this->methodsVector.push_back(methodDecl);
}

// --------- Class definitions for class MethodDeclaration ----------- //
MethodDeclaration::MethodDeclaration(char* type, char* methodName, class MethodArgs *methodArgs, class Block *block) {
    this->type = type;
    this->methodName = methodName;
    this->methodArgs = methodArgs;
    this->block = block;
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
