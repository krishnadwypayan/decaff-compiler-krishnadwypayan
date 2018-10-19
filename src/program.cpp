#include "Headers/program.h"

Program::Program(string name, class FieldDeclarations *fieldDecls) {
    this->className = std::move(name);
    this->fieldDeclarations = fieldDecls;
    cout << name << endl;
}