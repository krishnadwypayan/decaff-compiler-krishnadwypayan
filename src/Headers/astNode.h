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