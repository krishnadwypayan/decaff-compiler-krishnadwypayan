#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1

#include "astNode.h"

union Node {
    int number;
    char* value;

    class Program *program;
};

typedef union Node YYSTYPE;

class Program: public ASTnode {
private:
    // Name of the class that the Decaf Program begins with.
    string className;

    class FieldDeclarations *fieldDecs;

    class MethodDeclarations *methodDecs;

public:
    Program(string name);

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }

};

#endif