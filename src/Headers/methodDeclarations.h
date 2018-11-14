#ifndef DECAF_COMPILER_METHOD_DECLARATIONS_H
#define DECAF_COMPILER_METHOD_DECLARATIONS_H

#include "block.h"


class MethodDeclarations: public ASTnode {
private:
    vector<class MethodDeclaration*> methodsVector;

public:
    MethodDeclarations() = default;

    void addMethodDecl(class MethodDeclaration *methodDecl);    

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

};

class MethodArgs: public ASTnode {
private:
    vector<class MethodArg*> methodArgsVector;

public:
    MethodArgs() = default;

    void addMethodArg(class MethodArg *methodArg);

};

class MethodArg: public ASTnode {
private:
    // DataType of the arg
    char* type;

    // identifier of the arg
    char* name;

public:
    MethodArg(char* type, char* name);

};

#endif // !DECAF_COMPILER_METHOD_DECLARATIONS_H