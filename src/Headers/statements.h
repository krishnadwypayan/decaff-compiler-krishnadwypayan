#ifndef DECAF_COMPILER_STATEMENTS_H
#define DECAF_COMPILER_STATEMENTS_H

#include "block.h"


// ------------------------------------------------------------------------------
class AssignmentStmt: public Statement {
private:
    class Location *location;

    class Expression *expr;

    class AssgnOp *assgnOp;

public:
    AssignmentStmt(class Location *loc, class AssgnOp *op, class Expression *expr);

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

enum LocationType {
    normalLoc = 1, arrayLoc = 2
};

class Location: public Expression {
private:
    string id;

    LocationType locType;

    // If the locationType is array, then we have the expr
    class Expression *expr;

public:
    Location(string id);

    Location(string id, class Expression *expr);

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

class AssgnOp {
private:
    string assgnOp;

public:
    AssgnOp(string assgnOp);

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

// ------------------------------------------------------------------------------
class MethodCallStmt: public Statement {
protected:
    string methodName;

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
    MethodCall(string methodName, class MethodCallParams *methodCallParams);

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

class CalloutMethodCall: public MethodCallStmt {
private:
    class CalloutArgs* calloutArgs;

public:
    CalloutMethodCall(string calloutMethodName, class CalloutArgs *calloutArgs);

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
    string stringLit;

    class Expression *expr;

public:
    CalloutArg(string calloutArgStringLit);

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
    IfElseStmt(class Expression *expr, class Block *ifBlock);

    IfElseStmt(class Expression *expr, class Block *ifBlock, class Block *elseBlock);

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

// ------------------------------------------------------------------------------
class ForStmt: public Statement {
private:
    string id;

    class Expression *expr1;

    class Expression *expr2;

    class Block *block;

public:
    ForStmt(string id, class Expression *expr1, class Expression *expr2, class Block *block);

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

// ------------------------------------------------------------------------------
class ReturnStmt: public Statement {
private:
    class Expression *expr;

public:
    ReturnStmt();

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

    string otherLiteral;

public:
    Literal(int intLit, int litVal);

    Literal(string otherLiteral, int litVal);

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

// ------------------------------------------------------------------------------

class UnaryExpression: public Expression {
private:
    string op;

    class Expression *expr;

public:
    UnaryExpression(string op, class Expression *expr);

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

// ------------------------------------------------------------------------------

class BinaryExpression: public Expression {
private:
    class Expression *expr1;

    string op;

    class Expression *expr2;

public:
    BinaryExpression(class Expression *expr1, string op, class Expression *expr2);

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};



#endif // !DECAF_COMPILER_STATEMENTS_H