#ifndef DECAF_COMPILER_METHOD_DECLARATIONS_H
#define DECAF_COMPILER_METHOD_DECLARATIONS_H

#include "block.h"


class MethodDeclarations: public ASTnode {
private:
    vector<class MethodDeclaration*> methodsVector;

public:
    MethodDeclarations() = default;

    void addMethodDecl(class MethodDeclaration *methodDecl);    

    Value* codeGen(Context *context);

};

class MethodDeclaration: public ASTnode {
private:
    // method return type (int/boolean/void)
    char* type;

    // method name
    char* methodName;

    // Args for the method
    class MethodArgs *methodArgs;

    // Method block
    class Block *block;

public:
    MethodDeclaration(char* type, char* methodName, class MethodArgs *methodArgs, class Block *block);

    Value* codeGen(Context *context);
};

class MethodArgs: public ASTnode {
private:
    vector<class MethodArg*> methodArgsVector;

public:
    MethodArgs() = default;

    void addMethodArg(class MethodArg *methodArg);

    vector<class MethodArg*> getMethodArgs() {
        return methodArgsVector;
    }

};

class MethodArg: public ASTnode {
private:
    // DataType of the arg
    char* type;

    // identifier of the arg
    char* name;

public:
    MethodArg(char* type, char* name);

    char* getArgType() {
        return type;
    }

    char* getArgName() {
        return name;
    }

};

#endif // !DECAF_COMPILER_METHOD_DECLARATIONS_H