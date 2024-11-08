//
// Created by Rajarshi on 6/11/24.
//
#include "ExpressionVisitors.h"

void ExpressionPrinter::visit(const BinaryExpression &expr) const {
    ostream_ref << "[";
    expr.left->acceptVisitor(*this);
    ostream_ref << " " << expr._operator << " ";
    expr.right->acceptVisitor(*this);
    ostream_ref << "]";
}

void ExpressionPrinter::visit(const GroupingExpression &expr) const {
    ostream_ref << "[group ";
    expr.expression->acceptVisitor(*this);
    ostream_ref << "]";
}

void ExpressionPrinter::visit(const UnaryExpression &expr) const {
    ostream_ref << "[" << expr._operator << " ";
    expr.expression->acceptVisitor(*this);
    ostream_ref << "]";
}

void ExpressionPrinter::visit(const LiteralExpression &expr) const {
    ostream_ref << expr.value;
}

