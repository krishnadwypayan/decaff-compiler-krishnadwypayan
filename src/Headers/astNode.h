#ifndef DECAF_COMPILER_ASTNODE_H
#define DECAF_COMPILER_ASTNODE_H

#include <bits/stdc++.h>
using namespace std;


class Program;

class ASTvisitor {
public:

    virtual void visit(Program &program) = 0;

};

class ASTnode {
public:

    virtual ~ASTnode() {}

    virtual void accept(ASTvisitor& V) = 0;

};

#endif // !DECAF_COMPILER_ASTNODE_H