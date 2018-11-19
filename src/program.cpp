#include "Headers/program.h"

Program::Program(char* name, class FieldDeclarations *fieldDecls, class MethodDeclarations *methodDecls) {
    this->className = name;
    this->fieldDeclarations = fieldDecls;
    this->methodDeclarations = methodDecls;
    this->context = new Context();
}

Value* Program::codeGen() {
    Value *v;

    // codeGen() for fieldDeclarations
    v = fieldDeclarations->codeGen(this->context);
    if (v == nullptr) {
        cerr << "Invalid field declarations" << endl;
        return nullptr;
    }


    // codeGen() for methodDeclarations
    v = methodDeclarations->codeGen(context);
    if (v == nullptr) {
        cerr << "[error] method declarations returned null on code gen \n";
        return nullptr;
    }

    return v;
}