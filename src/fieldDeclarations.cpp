#include "Headers/fieldDeclarations.h"


// --------- Class definitions for class FieldDeclarations ----------- //
void FieldDeclarations::addFieldDeclaration(class FieldDeclaration *fieldDecl) {
    this->FieldDeclarationsVector.push_back(fieldDecl);
}
// ------------------------------------------------------------------- //


// --------- Class definitions for class FieldDeclaration ------------ //
FieldDeclaration::FieldDeclaration(string dataType, class Variables *vars) {
    this->dataType = dataType;
    this->variablesVector = vars->getVariablesVector();
}
// ------------------------------------------------------------------- //


// ------------- Class definitions for class Variables --------------- //
void Variables::addVariable(class Variable *var) {
    this->variablesVector.push_back(var);
}

vector<class Variable*> Variables::getVariablesVector() {
    return this->variablesVector;
}
// ------------------------------------------------------------------- //


// ------------- Class definitions for class Variable ----------------- //
Variable::Variable(string name) {
    this->type = VarType::normal;
    this->name = name;
}

Variable::Variable(string name, int size) {
    this->type = VarType::array;
    this->name = name;
    this->size = size;
}

string Variable::getVarName() {
    return this->name;
}

int Variable::getArraySize() {
    if (this->type == VarType::array) {
        return this->size;
    }

    return -1;
}
// ------------------------------------------------------------------- //