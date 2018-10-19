#ifndef DECAF_COMPILER_FIELD_DECLARATIONS_H
#define DECAF_COMPILER_FIELD_DECLARATIONS_H

#include "astNode.h"


class FieldDeclarations: public ASTnode {
private:
    vector<class FieldDeclaration*> FieldDeclarationsVector;

public:
    FieldDeclarations() = default;

    void addFieldDeclaration(class FieldDeclaration *fieldDecl);

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

class FieldDeclaration: public ASTnode {
private:
    // DataType of the variable(s)
    string dataType;

    // Variables list that is returned by the object of class Variables
    vector<class Variable*> variablesVector;

public:
    FieldDeclaration(string dataType, class Variables *vars);

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }

};

/* 
* This enum is used to specify the type of the variable declared
**/
enum VarType {
    array = 1, normal = 2
};

class Variables: public ASTnode {
private:
    vector<class Variable*> variablesVector;

public:
    Variables() = default;

    void addVariable(class Variable *var);

    vector<class Variable*> getVariablesVector();

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

class Variable: public ASTnode {
private:
    // Name of the variable (ID)
    string name;

    // VarType
    VarType type;

    // Size of the array (used only if type = array)
    int size;

public:
    // Constructor for normal type variable
    Variable(string name);

    // Constructor for array type variable
    Variable(string name, int size);

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }

    string getVarName();

    int getArraySize();
};

#endif // !DECAF_COMPILER_FIELD_DECLARATIONS_H