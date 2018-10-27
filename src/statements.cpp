#include "Headers/statements.h"

// ------------ Class definitions for class AssignmentStmt -------------- //
AssignmentStmt::AssignmentStmt(class Location *loc, class AssgnOp *op, class Expression *expr) {
    this->location = loc;
    this->assgnOp = op;
    this->expr = expr;
}

// --------------- Class definitions for class Location ---------------- //
Location::Location(string id) {
    this->exprType = ExprType::location;
    this->locType = LocationType::normal;
    this->id = id;
}

Location::Location(string id, class Expression *expr) {
    this->exprType = ExprType::location;
    this->locType = LocationType::array;
    this->id = id;
    this->expr = expr;
}

// --------------- Class definitions for class AssgnOp ---------------- //
AssgnOp::AssgnOp(string op) {
    this->assgnOp = op;
}

// ------------ Class definitions for class MethodCallStmt ------------ //
MethodCallStmt::MethodCallStmt(string methodName, class MethodCallParams *methodCallParams) {
    this->methodName = methodName;
    this->methodCallParams = methodCallParams;
}

// ----------- Class definitions for class MethodCallParams ----------- //
void MethodCallParams::addMethodCallParam(class Expression *expr) {
    this->methodCallParamsVector.push_back(expr);
}

// -------- Class definitions for class CalloutMethodCallStmt --------- //
CalloutMethodCallStmt::CalloutMethodCallStmt(string calloutMethodName, class CalloutArgs *calloutArgs) {
    this->calloutMethodName = calloutMethodName;
    this->calloutArgs = calloutArgs;
}

// ------------- Class definitions for class CalloutArgs -------------- //
void CalloutArgs::addCalloutArg(class CalloutArg *calloutArg) {
    this->calloutArgsVector.push_back(calloutArg);
}

CalloutArg::CalloutArg(string calloutArgStringLit) {
    this->stringLit = calloutArgStringLit;
}

CalloutArg::CalloutArg(class Expression *expr) {
    this->expr = expr;
}

// -------------- Class definitions for class ForStmt ---------------- //
ForStmt::ForStmt(string id, class Expression *expr1, class Expression *expr2, class Block *block) {
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

Literal::Literal(string otherLiteral, int litType) {
    this->exprType = ExprType::literal;
    this->litType = litType;
    this->otherLiteral = otherLiteral;
}

// --------- Class definitions for class UnaryExpression ----------- //
UnaryExpression::UnaryExpression(string op, class Expression *expr) {
    this->exprType = ExprType::unary;
    this->op = op;
    this->expr = expr;
}

// -------- Class definitions for class BinaryExpression ----------- //
BinaryExpression::BinaryExpression(class Expression *expr1, string op, class Expression *expr2) {
    this->exprType = ExprType::binary;
    this->expr1 = expr1;
    this->op = op;
    this->expr2 = expr2;
}