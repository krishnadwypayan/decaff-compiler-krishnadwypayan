#include "Headers/block.h"


// -------------- Class Definitions for class Block ------------------ //
Block::Block(class VarDeclarations *varDecls, class Statements *stmts) {
    this->varDecls = varDecls;
    this->stmts = stmts;
}

// --------- Class Definitions for class VarDeclarations ------------ //
void VarDeclarations::addVarDecl(class VarDeclaration *varDecl) {
    this->varDeclsVector.push_back(varDecl);
}

// ---------- Class Definitions for class VarDeclaration ------------ //
VarDeclaration::VarDeclaration(string type, class MoreIDs *moreIds) {
    this->type = type;
    this->moreIds = moreIds;
}

// ------------- Class Definitions for class MoreIDs --------------- //
void MoreIDs::addId(string id) {
    this->idVector.push_back(id);
}

// ----------- Class Definitions for class Statements -------------- //
void Statements::addStmt(class Statement *stmt) {
    this->stmtsVector.push_back(stmt);
}

// ------------ Class Definitions for class Statement -------------- //
