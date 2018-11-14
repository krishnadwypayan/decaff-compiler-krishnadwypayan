#ifndef DECAF_COMPILER_STATEMENTS_H
#define DECAF_COMPILER_STATEMENTS_H

#include "block.h"


// ------------------------------------------------------------------------------
class AssignmentStmt: public Statement {
private:
    class Location *location;

    class Expression *expr;

    char* assgnOp;

public:
    AssignmentStmt(class Location *loc, char* op, class Expression *expr);
};

enum LocationType {
    normalLoc = 1, arrayLoc = 2
};

class Location: public Expression {
private:
    char* id;

    LocationType locType;

    // If the locationType is array, then we have the expr
    class Expression *expr;

public:
    Location(char* id);

    Location(char* id, class Expression *expr);

};

class AssgnOp {
private:
    char* assgnOp;

public:
    AssgnOp(char* assgnOp);

};

// ------------------------------------------------------------------------------
class MethodCallStmt: public Statement, public Expression {
protected:
    char* methodName;

public:
    MethodCallStmt() = default;

};

class MethodCall: public MethodCallStmt {
private:
    class MethodCallParams* methodCallParams;

public:
    MethodCall(char* methodName, class MethodCallParams *methodCallParams);

};

class CalloutMethodCall: public MethodCallStmt {
private:
    class CalloutArgs* calloutArgs;

public:
    CalloutMethodCall(char* calloutMethodName, class CalloutArgs *calloutArgs);

};

class MethodCallParams: public ASTnode {
private:
    vector<class Expression*> methodCallParamsVector;

public:
    MethodCallParams() = default;

    void addMethodCallParam(class Expression *expr);

};

class CalloutArgs: public ASTnode {
private:
    vector<class CalloutArg*> calloutArgsVector;

public:
    CalloutArgs() = default;

    void addCalloutArg(class CalloutArg *calloutArg);

};

class CalloutArg: public ASTnode {
private:
    char* stringLit;

    class Expression *expr;

public:
    CalloutArg(char* calloutArgStringLit);

    CalloutArg(class Expression *expr);

};

// ------------------------------------------------------------------------------
class IfElseStmt: public Statement {
private:
    class Expression *ifExpr;

    class Block *ifBlock;

    class Block *elseBlock;

public:
    IfElseStmt(class Expression *expr, class Block *ifBlock, class Block *elseBlock);

};

// ------------------------------------------------------------------------------
class ForStmt: public Statement {
private:
    char* id;

    class Expression *expr1;

    class Expression *expr2;

    class Block *block;

public:
    ForStmt(char* id, class Expression *expr1, class Expression *expr2, class Block *block);

};

// ------------------------------------------------------------------------------
class ReturnStmt: public Statement {
private:
    class Expression *expr;

public:
    ReturnStmt(class Expression *expr);

};

// ------------------------------------------------------------------------------
class BreakStmt: public Statement {
public:
    BreakStmt() {}

};

// ------------------------------------------------------------------------------
class ContinueStmt: public Statement {
public:
    ContinueStmt() {}

};

// ------------------------------------------------------------------------------
class EnclosedExpression: public Expression {
private:
    class Expression *expr;

public:
    EnclosedExpression(class Expression *expr);

};

// ------------------------------------------------------------------------------
class Literal: public Expression {
private:
    // litType values : integer_literal = 1, char_literal = 2, bool_literal = 3
    int litType;

    int intLit;

    char* otherLiteral;

public:
    Literal(int intLit, int litVal);

    Literal(char* otherLiteral, int litVal);

};

// ------------------------------------------------------------------------------

class UnaryExpression: public Expression {
private:
    char* op;

    class Expression *expr;

public:
    UnaryExpression(char* op, class Expression *expr);

};

// ------------------------------------------------------------------------------

class BinaryExpression: public Expression {
private:
    class Expression *expr1;

    char* op;

    class Expression *expr2;

public:
    BinaryExpression(class Expression *expr1, char* op, class Expression *expr2);

};

#endif // !DECAF_COMPILER_STATEMENTS_H