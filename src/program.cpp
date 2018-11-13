#include "Headers/program.h"

Program::Program(char* name, class FieldDeclarations *fieldDecls, class MethodDeclarations *methodDecls) {
    this->className = name;
    this->fieldDeclarations = fieldDecls;
    this->methodDeclarations = methodDecls;
    cout << name << endl;
}