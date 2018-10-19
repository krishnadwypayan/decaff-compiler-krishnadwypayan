#ifndef DECAF_COMPILER_ASTNODE_H
#define DECAF_COMPILER_ASTNODE_H

#include <bits/stdc++.h>
using namespace std;


class Program;
class FieldDeclarations;
class FieldDeclaration;
class Variables;
class Variable;


class ASTvisitor {
public:

    virtual void visit(Program &program) = 0;

    virtual void visit(FieldDeclarations &fieldDecls) = 0;

    virtual void visit(FieldDeclaration &fieldDecl) = 0;

    virtual void visit(Variables &vars) = 0;

    virtual void visit(Variable &var) = 0;

};

class ASTnode {
public:

    virtual ~ASTnode() {}

    virtual void accept(ASTvisitor& V) = 0;

};

#endif // !DECAF_COMPILER_ASTNODE_H