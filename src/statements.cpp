#include "Headers/statements.h"

// ------------ Class definitions for class AssignmentStmt -------------- //
AssignmentStmt::AssignmentStmt(class Location *loc, char* op, class Expression *expr) {
    this->location = loc;
    this->assgnOp = op;
    this->expr = expr;
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

// --------------- Class definitions for class AssgnOp ---------------- //
AssgnOp::AssgnOp(char* op) {
    this->assgnOp = op;
}

// ------------ Class definitions for class MethodCallStmt ------------ //
MethodCall::MethodCall(char* methodName, class MethodCallParams *methodCallParams) {
    this->methodName = methodName;
    this->methodCallParams = methodCallParams;
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

// -------- Class definitions for class EnclosedExpression ---------- //
EnclosedExpression::EnclosedExpression(class Expression *expr) {
    this->exprType = ExprType::enclosedExpr;
    this->expr = expr;
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

// --------- Class definitions for class UnaryExpression ----------- //
UnaryExpression::UnaryExpression(char* op, class Expression *expr) {
    this->exprType = ExprType::unary;
    this->op = op;
    this->expr = expr;
}

// -------- Class definitions for class BinaryExpression ----------- //
BinaryExpression::BinaryExpression(class Expression *expr1, char* op, class Expression *expr2) {
    this->exprType = ExprType::binary;
    this->expr1 = expr1;
    this->op = op;
    this->expr2 = expr2;
}