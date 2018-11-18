#include "Headers/block.h"


// -------------- Class Definitions for class Block ------------------ //
Block::Block(class VarDeclarations *varDecls, class Statements *stmts) {
    this->varDecls = varDecls;
    this->stmts = stmts;
}

Value* Block::codeGen(Context *context) {
    Value *value;
    map<char*, AllocaInst*> oldMap;

    value = varDecls->codeGen(context, oldMap);
    if (value ==  nullptr) {
        cerr << "[error] Variable declarations returned null \n";
        return nullptr;
    }

    value = stmts->codeGen(context);

    // put the old variables back to the current scope
    for (auto it = oldMap.begin(); it != oldMap.end(); it++) {
        context->NamedValues[it->first] = oldMap[it->first];
    }

    return value;
}

// --------- Class Definitions for class VarDeclarations ------------ //
void VarDeclarations::addVarDecl(class VarDeclaration *varDecl) {
    this->varDeclsVector.push_back(varDecl);
}

Value* VarDeclarations::codeGen(Context *context, map<char*, AllocaInst*> &oldMap) {
    Value *value = ConstantInt::get(context->llvmContext, APInt(32, 1));

    for (auto &varDecl : varDeclsVector) {
        value = varDecl->codeGen(context, oldMap);
        if (value == nullptr) {
            cerr << "[error] Variable declaration returned null on codeGen \n";
            return value;
        }
    }

    return value;
}

// ---------- Class Definitions for class VarDeclaration ------------ //
VarDeclaration::VarDeclaration(char* type, class MoreIDs *moreIds) {
    this->type = type;
    this->moreIds = moreIds;
    this->idVector = this->moreIds->getIdVector();
}

vector<char*> VarDeclaration::getIdVector() {
    return this->idVector;
}

Value* VarDeclaration::codeGen(Context *context, map<char*, AllocaInst*> &oldMap) {
    // Get the function to whose scope this variable belongs to
    Function *function = context->builder->GetInsertBlock()->getParent();

    for (auto &var : idVector) {
        Value *initVal = nullptr;
        AllocaInst *allocaInst = nullptr;

        if (type == "int") {
            initVal = ConstantInt::get(context->llvmContext, APInt(32, 0));
            allocaInst = context->createLocalVarFunction(function, var, type);
        }
        else if (type == "boolean") {
            initVal = ConstantInt::get(context->llvmContext, APInt(1, 0));
            allocaInst = context->createLocalVarFunction(function, var, type);
        }

        oldMap[var] = context->NamedValues[var];
        context->NamedValues[var] = allocaInst;
    }

    return ConstantInt::get(context->llvmContext, APInt(32, 0));
}

// ------------- Class Definitions for class MoreIDs --------------- //
void MoreIDs::addId(char* id) {
    this->idVector.push_back(id);
}

vector<char*> MoreIDs::getIdVector() {
    return this->idVector;
}

// ----------- Class Definitions for class Statements -------------- //
void Statements::addStmt(class Statement *stmt) {
    this->stmtsVector.push_back(stmt);
}

Value* Statements::codeGen(Context *context) {
    Value *value = ConstantInt::get(context->llvmContext, APInt(32, 1));

    for (auto &stmt : stmtsVector) {
        value = stmt->codeGen(context);
    }

    return value;
}

// ------------ Class Definitions for class Statement -------------- //
