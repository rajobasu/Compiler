//
// Created by Rajarshi on 6/11/24.
//
#include "ExpressionVisitors.h"
#include "Operators.h"
#include <utility>

////////////////////////////////////////////////////////////////////////////
// ------------------------ Expression Printer -------------------------- //
////////////////////////////////////////////////////////////////////////////


void ExpressionPrinter::operator()(const BinaryExpression &expr) const {
    ostream_ref << "[";
    std::visit(*this, *(expr.left));
    ostream_ref << " " << expr._operator << " ";
    std::visit(*this, *(expr.right));
    ostream_ref << "]";
}

void ExpressionPrinter::operator()(const GroupingExpression &expr) const {
    ostream_ref << "[group ";
    std::visit(*this, *(expr.expression));
    ostream_ref << "]";
}

void ExpressionPrinter::operator()(const UnaryExpression &expr) const {
    ostream_ref << "[" << expr._operator << " ";
    std::visit(*this, *(expr.expression));
    ostream_ref << "]";
}

void ExpressionPrinter::operator()(const LiteralExpression &expr) const {
    ostream_ref << expr.value;
}

////////////////////////////////////////////////////////////////////////////
// ------------------------ Expression Evaluators ----------------------- //
////////////////////////////////////////////////////////////////////////////


Literal ExpressionEvaluator::operator()(const BinaryExpression &expr) const {
    Literal left = std::visit(*this, *(expr.left));
    Literal right = std::visit(*this, *(expr.right));
    switch (expr._operator.token_type) {
        case TokenType::PLUS: return std::visit(get_plus_operator_visitor(expr._operator), left, right);
        case TokenType::STAR: return std::visit(get_multiply_operator_visitor(expr._operator), left, right);
        case TokenType::LESS: return std::visit(get_le_operator_visitor(expr._operator), left, right);
        case TokenType::LESS_EQUAL: return std::visit(get_leq_operator_visitor(expr._operator), left, right);
        case TokenType::GREATER: return std::visit(get_ge_operator_visitor(expr._operator), left, right);
        case TokenType::GREATER_EQUAL: return std::visit(get_geq_operator_visitor(expr._operator), left, right);
        case TokenType::EQUAL_EQUAL: return std::visit(get_eq_operator_visitor(expr._operator), left, right);
        case TokenType::BANG_EQUAL: return std::visit(get_neq_operator_visitor(expr._operator), left, right);
        default: throw error_handling::runtime_exception(expr._operator, "Unknown binary operator");
    }
}

Literal ExpressionEvaluator::operator()(const UnaryExpression &expr) const {
    Literal val = std::visit(*this, *(expr.expression));
    switch (expr._operator.token_type) {
        case TokenType::MINUS: return std::visit(get_unary_minus_operator_visitor(expr._operator), val);
        case TokenType::PLUS: return std::visit(get_unary_plus_operator_visitor(expr._operator), val);
        case TokenType::BANG: return std::visit(get_unary_bang_operator_visitor(expr._operator), val);
        default: throw error_handling::runtime_exception(expr._operator, "Unknown unary operator");
    }
}


Literal ExpressionEvaluator::operator()(const GroupingExpression &expr) const {
    return std::visit(*this, *(expr.expression));
}

Literal ExpressionEvaluator::operator()(const LiteralExpression &expr) const {
    return expr.value;
}
