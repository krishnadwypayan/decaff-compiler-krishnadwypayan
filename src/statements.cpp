#include "Headers/statements.h"

// ------------ Class definitions for class AssignmentStmt -------------- //
AssignmentStmt::AssignmentStmt(class Location *loc, char* op, class Expression *expr) {
    this->location = loc;
    this->assgnOp = op;
    this->expr = expr;
}

Value* AssignmentStmt::codeGen(Context *context) {
    Value *currVal = context->NamedValues[location->getLoc()];
    
    if (currVal == nullptr) {
        currVal = context->moduleOb->getGlobalVariable(location->getLoc());
    }

    if (currVal == nullptr) {
        cerr << "[error] Variable not found \n";
        return nullptr;
    }

    Value *newVal = expr->codeGen(context);
    if (expr->getExprType() == ExprType::location) {
        newVal = context->builder->CreateLoad(newVal);
    }

    if (newVal == nullptr) {
        return nullptr;
    }

    Value *lVal = location->codeGen(context);
    currVal = context->builder->CreateLoad(lVal);

    if (assgnOp == "+=") {
        newVal = context->builder->CreateAdd(currVal, newVal, "plusEqualVal");
    }
    else if (assgnOp == "-=") {
        newVal = context->builder->CreateSub(currVal, newVal, "minusEqualVal");
    }

    return context->builder->CreateStore(newVal, lVal);
}

// --------------- Class definitions for class Location ---------------- //
Location::Location(char* id) {
    this->exprType = ExprType::location;
    this->locType = LocationType::normalLoc;
    this->id = id;
}

Location::Location(char* id, class Expression *expr) {
    this->exprType = ExprType::location;
    this->locType = LocationType::arrayLoc;
    this->id = id;
    this->expr = expr;
}

char* Location::getLoc() {
    return this->id;
}

Value* Location::codeGen(Context *context) {
    // try to get the value from the current scope
    Value *value = context->NamedValues[id];
    
    // check if the variable is a global variable, if it does not exist in the current scope
    if (value == nullptr) {
        value = context->moduleOb->getNamedGlobal(id);
    }

    // return null if the value is still null
    if (value == nullptr) {
        cerr << "[error] Variable not found \n";
        return nullptr;
    }

    // if location is a variable, return the code generated
    if (this->locType == LocationType::normalLoc) {
        return value;
    }

    // check if array index is null
    if (this->expr == nullptr) {
        cerr << "[error] Array index is null\n";
        return nullptr;
    }

    // code gen for the array index
    Value *arrayIndex = expr->codeGen(context);

    if (expr->getExprType() == ExprType::location) {
        arrayIndex = context->builder->CreateLoad(arrayIndex);
    }

    if (arrayIndex == nullptr) {
        cerr << "[error] codeGen() for arrayIndex generated null \n";
        return nullptr;
    }

    vector<Value*> arrayIndexVec;
    arrayIndexVec.push_back(context->builder->getInt32(0));
    arrayIndexVec.push_back(arrayIndex);
    value = context->builder->CreateGEP(value, arrayIndexVec, id);
    return value;
}

// --------------- Class definitions for class AssgnOp ---------------- //
AssgnOp::AssgnOp(char* op) {
    this->assgnOp = op;
}

// ------------ Class definitions for class MethodCallStmt ------------ //
MethodCall::MethodCall(char* methodName, class MethodCallParams *methodCallParams) {
    this->methodName = methodName;
    this->methodCallParams = methodCallParams;
}

Value* MethodCall::codeGen(Context *context) {
    Function *callee = context->moduleOb->getFunction(methodName);
    if (callee == nullptr) {
        cerr << "[error] Unknown function referenced \n";
        return nullptr;
    }

    vector<class Expression*> methodCallParamsVector = methodCallParams->getMethodCallParamsVector();
    if (callee->arg_size() != methodCallParamsVector.size()) {
        cerr << "[error] Incorrect number of arguments passed \n";
        return nullptr;
    }

    vector<Value *> ArgsV;
    for (auto &param : methodCallParamsVector) {
        Value *argVal = param->codeGen(context);
        if (param->getExprType() == ExprType::location) {
            argVal = context->builder->CreateLoad(argVal);
        }

        if (argVal == nullptr) {
            cerr << "[error] Invalid argument \n";
            return nullptr;
        }

        ArgsV.push_back(argVal);
    }

    return context->builder->CreateCall(callee, ArgsV, "MethodCall");
}

// ----------- Class definitions for class MethodCallParams ----------- //
void MethodCallParams::addMethodCallParam(class Expression *expr) {
    this->methodCallParamsVector.push_back(expr);
}

// -------- Class definitions for class CalloutMethodCallStmt --------- //
CalloutMethodCall::CalloutMethodCall(char* calloutMethodName, class CalloutArgs *calloutArgs) {
    this->methodName = calloutMethodName;
    this->calloutArgs = calloutArgs;
}

Value* CalloutMethodCall::codeGen(Context *context) {
    vector<Type*> argTypes;
    vector<Value*> args;
    vector<class CalloutArg*> calloutArgsVector = calloutArgs->getCalloutArgsVector();

    for (auto &arg : calloutArgsVector) {
        Value *argValue = arg->codeGen(context);
        if (argValue == nullptr) {
            cerr << "[error] Callout arg codeGen returned null \n";
            return nullptr;
        }
        args.push_back(argValue);
        argTypes.push_back(argValue->getType());
    }

    ArrayRef<Type*> paramTypesVector(argTypes);
    ArrayRef<Value*> paramsVector(args);
    FunctionType *funcType = FunctionType::get(Type::getInt32Ty(context->llvmContext, paramTypesVector, false));
    Constant *func = context->moduleOb->getOrInsertFunction(methodName, funcType);
    if (func == nullptr) {
        cerr << "[error] callout method not found \n";
        return nullptr;
    }

    return context->builder->CreateCall(func, paramsVector);
}

// ------------- Class definitions for class CalloutArgs -------------- //
void CalloutArgs::addCalloutArg(class CalloutArg *calloutArg) {
    this->calloutArgsVector.push_back(calloutArg);
}

CalloutArg::CalloutArg(char* calloutArgStringLit) {
    this->stringLit = calloutArgStringLit;
}

CalloutArg::CalloutArg(class Expression *expr) {
    this->expr = expr;
}

Value* CalloutArg::codeGen(Context *context) {
    Value *value = expr->codeGen(context);
    if (expr->getExprType() == ExprType::location) {
        value = context->builder->CreateLoad(value);
    }
    return value;
}

// ------------- Class definitions for class IfElseStmt -------------- //
IfElseStmt::IfElseStmt(class Expression *expr, class Block *ifBlock, class Block *elseBlock) {
    this->ifExpr = expr;
    this->ifBlock = ifBlock;
    this->elseBlock = elseBlock;
}

// -------------- Class definitions for class ForStmt ---------------- //
ForStmt::ForStmt(char* id, class Expression *expr1, class Expression *expr2, class Block *block) {
    this->id = id;
    this->expr1 = expr1;
    this->expr2 = expr2;
    this->block = block;
}

// -------------- Class definitions for class ForStmt ---------------- //
ReturnStmt::ReturnStmt(class Expression *expr) {
    this->expr = expr;
}

Value* ReturnStmt::codeGen(Context *context) {
    if (expr != nullptr) {
        Value *value = expr->codeGen(context);
        if (expr->getExprType() == ExprType::location) {
            value = context->builder->CreateLoad(value);
        }

        return context->builder->CreateRet(value);
    }

    return context->builder->CreateRetVoid();
}

// -------- Class definitions for class EnclosedExpression ---------- //
EnclosedExpression::EnclosedExpression(class Expression *expr) {
    this->exprType = ExprType::enclosedExpr;
    this->expr = expr;
}

Value* EnclosedExpression::codeGen(Context *context) {
    return expr->codeGen(context);
}

// -------------- Class definitions for class Literal --------------- //
Literal::Literal(int litVal, int litType) {
    this->exprType = ExprType::literal;
    this->litType = litType;
    this->intLit = litVal;
}

Literal::Literal(char* otherLiteral, int litType) {
    this->exprType = ExprType::literal;
    this->litType = litType;
    this->otherLiteral = otherLiteral;
}

Value* Literal::codeGen(Context *context) {
    if (this->litType == 1) {
        // integer literal
        return ConstantInt::get(context->llvmContext, APInt(32, static_cast<uint64_t>(this->intLit)));
    }
    else if (this->litType == 2) {
        // char literal
        return context->builder->CreateGlobalStringPtr(this->otherLiteral);
    }
    else {
        // boolean literal
        bool val = this->otherLiteral == "true" ? true : false;
        return ConstantInt::get(context->llvmContext, APInt(1, val));
    }

    return nullptr;
}

// --------- Class definitions for class UnaryExpression ----------- //
UnaryExpression::UnaryExpression(char* op, class Expression *expr) {
    this->exprType = ExprType::unary;
    this->op = op;
    this->expr = expr;
}

Value* UnaryExpression::codeGen(Context *context) {
    Value *value = expr->codeGen(context);
    
    if (exprType == ExprType::location) {
        value = context->builder->CreateLoad(value);
    }

    if (op == "-") {
        return context->builder->CreateNeg(value, "negVal");
    }
    else if (op == "!") {
        return context->builder->CreateNot(value, "notVal");
    }

    return nullptr;
}

// -------- Class definitions for class BinaryExpression ----------- //
BinaryExpression::BinaryExpression(class Expression *expr1, char* op, class Expression *expr2) {
    this->exprType = ExprType::binary;
    this->expr1 = expr1;
    this->op = op;
    this->expr2 = expr2;
}

Value* BinaryExpression::codeGen(Context *context) {
    Value *lVal = expr1->codeGen(context);
    Value *rVal = expr2->codeGen(context);
    
    if (expr1->getExprType() == ExprType::location) {
        lVal = context->builder->CreateLoad(lVal);
    }

    if (expr2->getExprType() == ExprType::location) {
        rVal = context->builder->CreateLoad(rVal);
    }

    if (op == "+") {
        return context->builder->CreateAdd(lVal, rVal, "addVal");
    }
    else if (op == "-") {
        return context->builder->CreateSub(lVal, rVal, "subVal");
    }
    else if (op == "*") {
        return context->builder->CreateMul(lVal, rVal, "mulVal");
    }
    else if (op == "/") {
        return context->builder->CreateSDiv(lVal, rVal, "divVal");
    }
    else if (op == "%") {
        return context->builder->CreateSRem(lVal, rVal, "modVal");
    }
    else if (op == "<") {
        return context->builder->CreateICmpSLT(lVal, rVal, "modVal");
    }
    else if (op == "<=") {
        return context->builder->CreateICmpSLE(lVal, rVal, "modVal");
    }
    else if (op == ">") {
        return context->builder->CreateICmpSGT(lVal, rVal, "modVal");
    }
    else if (op == ">=") {
        return context->builder->CreateICmpSGE(lVal, rVal, "modVal");
    }
    else if (op == "==") {
        return context->builder->CreateICmpEQ(lVal, rVal, "modVal");
    }
    else if (op == "!=") {
        return context->builder->CreateICmpNE(lVal, rVal, "modVal");
    }
    else if (op == "&&") {
        return context->builder->CreateAnd(lVal, rVal, "modVal");
    }
    else if (op == "||") {
        return context->builder->CreateOr(lVal, rVal, "modVal");
    }

    return nullptr;
}