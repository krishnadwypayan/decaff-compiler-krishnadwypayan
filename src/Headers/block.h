#ifndef DECAF_COMPILER_BLOCK_H
#define DECAF_COMPILER_BLOCK_H

#include "astNode.h"

class VarDeclarations: public ASTnode {
private:
    vector<class VarDeclaration*> varDeclsVector;

public:
    VarDeclarations() = default;

    void addVarDecl(class VarDeclaration *varDecl);

};

class VarDeclaration: public ASTnode {
private:
    // Datatype of the variable
    char* type;

    // object to the MoreIDs class that contains the vector of IDs of the particular type
    class MoreIDs *moreIds;

public:
    VarDeclaration(char* type, class MoreIDs *moreIds);

};

class MoreIDs: public ASTnode {
private:
    // Vector of all the IDs
    vector<char*> idVector;

public:
    MoreIDs() = default;

    void addId(char* id);

};

// -------------------------------------------------------------------------------
class Statements: public ASTnode {
private:
    vector<class Statement*> stmtsVector;

public:
    Statements() = default;

    void addStmt(class Statement *stmt);

};

// Type of statements
// AssignmentStmt, MethodCallStmt, IfElseStmt, 
// ForStmt, ReturnStmt, BreakStmt, ContinueStmt, BlockStmt

class Statement: public ASTnode {
public:
    Statement() = default;

};

// -------------------------------------------------------------------------------

class Block: public Statement {
private:
    class VarDeclarations *varDecls;

    class Statements *stmts;

public:
    Block(class VarDeclarations *varDecls, class Statements *stmts);

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

};

// -------------------------------------------------------------------------------

#endif // !DECAF_COMPILER_BLOCK_H