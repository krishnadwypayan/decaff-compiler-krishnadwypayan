#ifndef DECAF_COMPILER_BLOCK_H
#define DECAF_COMPILER_BLOCK_H

#include "astNode.h"

class VarDeclarations: public ASTnode {
private:
    vector<class VarDeclaration*> varDeclsVector;

public:
    VarDeclarations() = default;

    void addVarDecl(class VarDeclaration *varDecl);

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

class VarDeclaration: public ASTnode {
private:
    // Datatype of the variable
    string type;

    // object to the MoreIDs class that contains the vector of IDs of the particular type
    class MoreIDs *moreIds;

public:
    VarDeclaration(string type, class MoreIDs *moreIds);

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

class MoreIDs: public ASTnode {
private:
    // Vector of all the IDs
    vector<string> idVector;

public:
    MoreIDs() = default;

    void addId(string id);

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

// -------------------------------------------------------------------------------
class Statements: public ASTnode {
private:
    vector<class Statement*> stmtsVector;

public:
    Statements() = default;

    void addStmt(class Statement *stmt);

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

// Type of statements
// AssignmentStmt, MethodCallStmt, IfElseStmt, 
// ForStmt, ReturnStmt, BreakStmt, ContinueStmt, BlockStmt

class Statement: public ASTnode {
public:
    Statement() = default;

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

// -------------------------------------------------------------------------------

class Block: public Statement {
private:
    class VarDeclarations *varDecls;

    class Statements *stmts;

public:
    Block(class VarDeclarations *varDecls, class Statements *stmts);

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

// -------------------------------------------------------------------------------
enum ExprType {
    unary = 1, binary = 2, enclosedExpr = 3, location = 4, literal = 5
};

class Expression: public ASTnode {
protected:
    ExprType exprType;

public:
    Expression() = default;

    virtual void accept(ASTvisitor &v) {
        v.visit(*this);
    }
};

// -------------------------------------------------------------------------------

#endif // !DECAF_COMPILER_BLOCK_H