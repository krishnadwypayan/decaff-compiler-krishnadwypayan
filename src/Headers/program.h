#ifndef DECAF_COMPILER_PROGRAM_H
#define DECAF_COMPILER_PROGRAM_H

#endif // !DECAF_COMPILER_PROGRAM_H

#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1

#include "astNode.h"
#include "fieldDeclarations.h"
#include "methodDeclarations.h"
#include "block.h"
#include "statements.h"

union Node {
    int number;
    char* value;

    class Program *program;

    class FieldDeclarations *fieldDeclarations;

    class FieldDeclaration *fieldDeclaration;

    class Variables *vars;

    class Variable *var;

    class MethodDeclarations *methodDeclarations;

    class MethodDeclaration *methodDeclaration;

    class MethodArgs *methodArgs;

    class MethodArg *methodArg;

    class Block *block;

    class VarDeclarations *varDeclarations;

    class VarDeclaration *varDeclaration;

    class MoreIDs *moreIds;

    class Statements *stmts;

    class Statement *stmt;

    class AssignmentStmt *assgnStmt;

    class Location *loc;

    class Expression *expr;

    class AssgnOp *assgnOp;

    class MethodCall *methodCall;

    class MethodCallStmt *methodCallStmt;

    class MethodCallParams *methodCallParams;

    class CalloutArgs *calloutArgs;

    class CalloutArg *calloutArg;

    class Literal *literal;
};

typedef union Node YYSTYPE;

class Program: public ASTnode {
private:
    // Name of the class that the Decaf Program begins with.
    char* className;

    class FieldDeclarations *fieldDeclarations;

    class MethodDeclarations *methodDeclarations;


public:
    Program(char* name, class FieldDeclarations *fieldDecls, class MethodDeclarations *methodDecls);

};

#endif