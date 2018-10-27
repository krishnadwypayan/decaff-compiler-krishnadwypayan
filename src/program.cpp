#include "Headers/program.h"

Program::Program(string name, class FieldDeclarations *fieldDecls, class MethodDeclarations *methodDecls) {
    this->className = std::move(name);
    this->fieldDeclarations = fieldDecls;
    this->methodDeclarations = methodDecls;
    cout << name << endl;
}