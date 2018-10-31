#ifndef DECAF_COMPILER_ASTNODE_H
#define DECAF_COMPILER_ASTNODE_H

#include <bits/stdc++.h>
using namespace std;


class Program;
class FieldDeclarations;
class FieldDeclaration;
class Variables;
class Variable;
class MethodDeclarations;
class MethodDeclaration;
class MethodArgs;
class MethodArg;
class Block;
class VarDeclarations;
class VarDeclaration;
class MoreIDs;
class Statements;
class Statement;
class Expression;
class AssignmentStmt;
class Location;
class AssgnOp;
class MethodCallStmt;
class MethodCall;
class CalloutMethodCall;
class MethodCallParams;
class CalloutArgs;
class CalloutArg;
class IfElseStmt;
class ForStmt;
class ReturnStmt;
class BreakStmt;
class ContinueStmt;
class EnclosedExpression;
class Literal;
class UnaryExpression;
class BinaryExpression;

class ASTvisitor {
public:

    virtual void visit(Program &program) = 0;

    virtual void visit(FieldDeclarations &fieldDecls) = 0;

    virtual void visit(FieldDeclaration &fieldDecl) = 0;

    virtual void visit(Variables &vars) = 0;

    virtual void visit(Variable &var) = 0;

    virtual void visit(MethodDeclarations &methodDecls);

    virtual void visit(MethodDeclaration &methodDecl);

    virtual void visit(MethodArgs &methodArgs);

    virtual void visit(MethodArg &methodArg);

    virtual void visit(Block &block);

    virtual void visit(VarDeclarations &varDecls);

    virtual void visit(VarDeclaration &varDecl);

    virtual void visit(MoreIDs &moreIds);

    virtual void visit(Statements &stmts);

    virtual void visit(Statement &stmt);

    virtual void visit(Expression &expr);

    virtual void visit(AssignmentStmt &assgnStmt);

    virtual void visit(Location &loc);
    
    virtual void visit(AssgnOp &assgnOp);
    
    virtual void visit(MethodCallStmt &methCallStmt);

    virtual void visit(MethodCall &methCall);
    
    virtual void visit(CalloutMethodCall &calloutMethCallStmt);
    
    virtual void visit(MethodCallParams &methCallParams);
    
    virtual void visit(CalloutArgs &calloutArgs);
    
    virtual void visit(CalloutArg &calloutArg);
    
    virtual void visit(IfElseStmt &ifElseStmt);
    
    virtual void visit(ForStmt &forStmt);
    
    virtual void visit(ReturnStmt &retStmt);
    
    virtual void visit(BreakStmt &brkStmt);
    
    virtual void visit(ContinueStmt &continueStmt);
    
    virtual void visit(EnclosedExpression &enclExpr);
    
    virtual void visit(Literal &lit);

    virtual void visit(UnaryExpression &unaryExpr);
    
    virtual void visit(BinaryExpression &binExpr);

};

class ASTnode {
public:

    virtual ~ASTnode() {}

    virtual void accept(ASTvisitor& V) = 0;

};

#endif // !DECAF_COMPILER_ASTNODE_H