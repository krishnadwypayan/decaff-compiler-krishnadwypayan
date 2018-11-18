#include "Headers/fieldDeclarations.h"


// --------- Class definitions for class FieldDeclarations ----------- //
void FieldDeclarations::addFieldDeclaration(class FieldDeclaration *fieldDecl) {
    this->FieldDeclarationsVector.push_back(fieldDecl);
}

Value* FieldDeclarations::codeGen(Context *context) {
    // call the codeGen() for every fieldDeclaration added to the vector
    for (auto &fieldDecl : FieldDeclarationsVector) {
        fieldDecl->codeGen(context);
    }

    Value *v = ConstantInt::get(context->llvmContext, APInt(32, 1));
    return v;
}

// --------- Class definitions for class FieldDeclaration ------------ //
FieldDeclaration::FieldDeclaration(char* dataType, class Variables *vars) {
    this->dataType = dataType;
    this->variablesVector = vars->getVariablesVector();
}

Value* FieldDeclaration::codeGen(Context *context) {
    Type *type = nullptr;

    if (dataType == "int") {
        type = Type::getInt32Ty(context->llvmContext);
    }
    else if (dataType == "boolean") {
        type = Type::getInt1Ty(context->llvmContext);
    }

    // create a global variable or every var according to the type (Array or normal)
    for (auto var : variablesVector) {
        if (var->isArray()) {
            ArrayType *arrType = ArrayType::get(type, var->getArraySize());

            // Linkage is what determines if multiple declarations of the same object 
            // refer to the same object, or to separate ones.
            GlobalVariable *globalVar = new GlobalVariable(*(context->moduleOb), arrType, false, 
                                            GlobalValue::ExternalLinkage, nullptr, var->getVarName());
            
            // Set the initializer for this global variable, removing any 
            // existing initializer if InitVal==NULL.
            // If this GV has type T*, the initializer must have type T.
            globalVar->setInitializer(ConstantAggregateZero::get(arrType));
        }
        else {
            GlobalVariable *globalVar = new GlobalVariable(*(context->moduleOb), type, false, 
                                            GlobalValue::ExternalLinkage, nullptr, var->getVarName());
            globalVar->setInitializer(Constant::getNullValue(type));
        }
    }

    // Return a ConstantInt with the specified value and an implied Type.
    // The type is the integer type that corresponds to the bit width of the value.
    Value *v = ConstantInt::get(context->llvmContext, APInt(32, 1));
    return v;
}

// ------------- Class definitions for class Variables --------------- //
void Variables::addVariable(class Variable *var) {
    this->variablesVector.push_back(var);
}

vector<class Variable*> Variables::getVariablesVector() {
    return this->variablesVector;
}

// ------------- Class definitions for class Variable ----------------- //
Variable::Variable(char* name) {
    this->type = VarType::normal;
    this->name = name;
}

Variable::Variable(char* name, int size) {
    this->type = VarType::array;
    this->name = name;
    this->size = size;
}

string Variable::getVarName() {
    return this->name;
}

int Variable::getArraySize() {
    if (type == VarType::array) {
        return size;
    }

    return -1;
}

bool Variable::isArray() {
    if (type == VarType::array) {
        return true;
    }

    return false;
}
