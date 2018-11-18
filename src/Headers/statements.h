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

    Value* codeGen(Context *context);
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

    char* getLoc();

    Value* codeGen(Context *context);

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

    Value* codeGen(Context *context) override {}

};

class MethodCall: public MethodCallStmt {
private:
    class MethodCallParams* methodCallParams;

public:
    MethodCall(char* methodName, class MethodCallParams *methodCallParams);

    Value* codeGen(Context *context);

};

class CalloutMethodCall: public MethodCallStmt {
private:
    class CalloutArgs* calloutArgs;

public:
    CalloutMethodCall(char* calloutMethodName, class CalloutArgs *calloutArgs);

    Value* codeGen(Context *context);

};

class MethodCallParams: public ASTnode {
private:
    vector<class Expression*> methodCallParamsVector;

public:
    MethodCallParams() = default;

    void addMethodCallParam(class Expression *expr);

    vector<class Expression*> getMethodCallParamsVector() {
        return methodCallParamsVector;
    }

};

class CalloutArgs: public ASTnode {
private:
    vector<class CalloutArg*> calloutArgsVector;

public:
    CalloutArgs() = default;

    void addCalloutArg(class CalloutArg *calloutArg);

    vector<class CalloutArg*> getCalloutArgsVector() {
        return calloutArgsVector;
    }

};

class CalloutArg: public ASTnode {
private:
    char* stringLit;

    class Expression *expr;

public:
    CalloutArg(char* calloutArgStringLit);

    CalloutArg(class Expression *expr);

    Value* codeGen(Context *context);

};

// ------------------------------------------------------------------------------
class IfElseStmt: public Statement {
private:
    class Expression *ifExpr;

    class Block *ifBlock;

    class Block *elseBlock;

public:
    IfElseStmt(class Expression *expr, class Block *ifBlock, class Block *elseBlock);

    Value* codeGen(Context *context);

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

    Value* codeGen(Context *context);

};

// ------------------------------------------------------------------------------
class ReturnStmt: public Statement {
private:
    class Expression *expr;

public:
    ReturnStmt(class Expression *expr);

    Value* codeGen(Context *context);

};

// ------------------------------------------------------------------------------
class BreakStmt: public Statement {
public:
    BreakStmt() {}

    Value *codeGen(Context *context);

};

// ------------------------------------------------------------------------------
class ContinueStmt: public Statement {
public:
    ContinueStmt() {}

    Value* codeGen(Context *context);

};

// ------------------------------------------------------------------------------
class EnclosedExpression: public Expression {
private:
    class Expression *expr;

public:
    EnclosedExpression(class Expression *expr);

    Value* codeGen(Context *context);

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

    Value* codeGen(Context *context);

};

// ------------------------------------------------------------------------------

class UnaryExpression: public Expression {
private:
    char* op;

    class Expression *expr;

public:
    UnaryExpression(char* op, class Expression *expr);

    Value* codeGen(Context *context);

};

// ------------------------------------------------------------------------------

class BinaryExpression: public Expression {
private:
    class Expression *expr1;

    char* op;

    class Expression *expr2;

public:
    BinaryExpression(class Expression *expr1, char* op, class Expression *expr2);

    Value* codeGen(Context *context);

};

#endif // !DECAF_COMPILER_STATEMENTS_H