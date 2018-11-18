#ifndef DECAF_COMPILER_BLOCK_H
#define DECAF_COMPILER_BLOCK_H

#include "astNode.h"

class VarDeclarations: public ASTnode {
private:
    vector<class VarDeclaration*> varDeclsVector;

public:
    VarDeclarations() = default;

    void addVarDecl(class VarDeclaration *varDecl);

    Value* codeGen(Context *context, map<char*, AllocaInst*> &oldMap);

};

class VarDeclaration: public ASTnode {
private:
    // Datatype of the variable
    char* type;

    // object to the MoreIDs class that contains the vector of IDs of the particular type
    class MoreIDs *moreIds;

    // vector of all the IDs
    vector<char*> idVector;

public:
    VarDeclaration(char* type, class MoreIDs *moreIds);

    vector<char*> getIdVector();

    Value* codeGen(Context *context, map<char*, AllocaInst*> &oldMap);

};

class MoreIDs: public ASTnode {
private:
    // Vector of all the IDs
    vector<char*> idVector;

public:
    MoreIDs() = default;

    void addId(char* id);

    vector<char*> getIdVector();

};

// -------------------------------------------------------------------------------
class Statements: public ASTnode {
private:
    vector<class Statement*> stmtsVector;

public:
    Statements() = default;

    void addStmt(class Statement *stmt);

    Value* codeGen(Context *context);

};

// Type of statements
// AssignmentStmt, MethodCallStmt, IfElseStmt, 
// ForStmt, ReturnStmt, BreakStmt, ContinueStmt, BlockStmt

class Statement: public ASTnode {
public:
    Statement() = default;

    Value* codeGen(Context *context) {}

};

// -------------------------------------------------------------------------------

class Block: public Statement {
private:
    class VarDeclarations *varDecls;

    class Statements *stmts;

public:
    Block(class VarDeclarations *varDecls, class Statements *stmts);

    Value *codeGen(Context *context);

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

    ExprType getExprType() { 
        return exprType;
    }

    virtual Value* codeGen(Context *context);

};

// -------------------------------------------------------------------------------

#endif // !DECAF_COMPILER_BLOCK_H