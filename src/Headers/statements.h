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

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
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

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

class AssgnOp {
private:
    char* assgnOp;

public:
    AssgnOp(char* assgnOp);

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

// ------------------------------------------------------------------------------
class MethodCallStmt: public Statement, public Expression {
protected:
    char* methodName;

public:
    MethodCallStmt() = default;

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

class MethodCall: public MethodCallStmt {
private:
    class MethodCallParams* methodCallParams;

public:
    MethodCall(char* methodName, class MethodCallParams *methodCallParams);

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

class CalloutMethodCall: public MethodCallStmt {
private:
    class CalloutArgs* calloutArgs;

public:
    CalloutMethodCall(char* calloutMethodName, class CalloutArgs *calloutArgs);

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

class MethodCallParams: public ASTnode {
private:
    vector<class Expression*> methodCallParamsVector;

public:
    MethodCallParams() = default;

    void addMethodCallParam(class Expression *expr);

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

class CalloutArgs: public ASTnode {
private:
    vector<class CalloutArg*> calloutArgsVector;

public:
    CalloutArgs() = default;

    void addCalloutArg(class CalloutArg *calloutArg);

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

class CalloutArg: public ASTnode {
private:
    char* stringLit;

    class Expression *expr;

public:
    CalloutArg(char* calloutArgStringLit);

    CalloutArg(class Expression *expr);

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

// ------------------------------------------------------------------------------
class IfElseStmt: public Statement {
private:
    class Expression *ifExpr;

    class Block *ifBlock;

    class Block *elseBlock;

public:
    IfElseStmt(class Expression *expr, class Block *ifBlock, class Block *elseBlock);

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
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

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

// ------------------------------------------------------------------------------
class ReturnStmt: public Statement {
private:
    class Expression *expr;

public:
    ReturnStmt(class Expression *expr);

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

// ------------------------------------------------------------------------------
class BreakStmt: public Statement {
public:
    BreakStmt() {}

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

// ------------------------------------------------------------------------------
class ContinueStmt: public Statement {
public:
    ContinueStmt() {}

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

// ------------------------------------------------------------------------------
class EnclosedExpression: public Expression {
private:
    class Expression *expr;

public:
    EnclosedExpression(class Expression *expr);

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
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

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

// ------------------------------------------------------------------------------

class UnaryExpression: public Expression {
private:
    char* op;

    class Expression *expr;

public:
    UnaryExpression(char* op, class Expression *expr);

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

// ------------------------------------------------------------------------------

class BinaryExpression: public Expression {
private:
    class Expression *expr1;

    char* op;

    class Expression *expr2;

public:
    BinaryExpression(class Expression *expr1, char* op, class Expression *expr2);

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};



#endif // !DECAF_COMPILER_STATEMENTS_H