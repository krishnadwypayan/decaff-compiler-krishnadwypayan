#ifndef DECAF_COMPILER_PROGRAM_H
#define DECAF_COMPILER_PROGRAM_H

#endif // !DECAF_COMPILER_PROGRAM_H

#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1

#include "astNode.h"
#include "fieldDeclarations.h"

union Node {
    int number;
    char* value;

    class Program *program;

    class FieldDeclarations *fieldDeclarations;

    class FieldDeclaration *fieldDeclaration;

    class Variables *vars;

    class Variable *var;
};

typedef union Node YYSTYPE;

class Program: public ASTnode {
private:
    // Name of the class that the Decaf Program begins with.
    string className;

    class FieldDeclarations *fieldDeclarations;


public:
    Program(string name, class FieldDeclarations *fieldDecls);

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }

};

#endif